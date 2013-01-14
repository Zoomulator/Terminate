#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <Terminate/terminate.hpp>
#include <Terminate/sdl/context.hpp>

// Possible movement. Each direction has dx,dy and a flag bit
enum { North=1, East=2, South=4, West=8 };
const int dirs[4][3] = { {0,-1,North}, {1,0,East}, {0,1,South}, {-1,0,West} };
enum { IsWall=0, IsPath, IsToken, IsDoor };

SDL_Surface* screen;

struct
LabData
	{
	typedef std::vector<Uint8> WallData;
	typedef std::vector<Uint32> TokenData;
	Uint8 width, height;
	Term::CharBuffer symbuf;
	WallData walls;
	TokenData tokens;
	size_t xplayer, yplayer;
	Uint32 door;
	bool win;

	LabData( Uint8 w, Uint8 h ) :
		width(w), height(h),
		symbuf(w,h)
		{}
	};


bool
InBounds( LabData& lab, int x, int y )
	{
	return 	x < lab.width  && x >= 0 &&
			y < lab.height && y >= 0;
	}


Uint32
PlaceRandomly( LabData& lab, int tile )
	{
	Uint32 ipos;
	do ipos = rand() % (lab.width*lab.height);
	while( lab.walls[ipos] == IsWall );
	
	lab.walls[ipos] = tile;
	return ipos;
	}


void
MovePlayer( LabData& lab, int dx, int dy )
	{
	int xnew = lab.xplayer + dx;
	int ynew = lab.yplayer + dy;
	Uint32 inew = xnew + ynew * lab.width;
	Uint8& tile = lab.walls[ inew ]; 
	if( InBounds( lab, xnew, ynew ) &&
		 tile != IsWall )
		{
		lab.xplayer = xnew;
		lab.yplayer = ynew;
		}
	if( tile == IsToken )
		{
		tile = IsPath;
		lab.tokens.erase( 
			remove( begin(lab.tokens), end(lab.tokens), inew ),
			end(lab.tokens));
		}
	if( lab.door == 0 && lab.tokens.empty() )
		lab.door = PlaceRandomly( lab, IsDoor );
	if( inew == lab.door )
		lab.win = true;
	}


void
GenerateLabyrinth( LabData& lab )
	{
	size_t labSize = lab.width * lab.height;
	lab.walls.resize( labSize, IsWall );
	lab.door = 0;
	lab.win = false;
	std::vector<Uint32> path; // Stack for backtracking. 
	int xstart = rand() % lab.width;
	int ystart = rand() % lab.height;
	xstart += xstart%2 ? 0 : 1;
	ystart += ystart%2 ? 0 : 1; // Start on even coordinate.
	path.push_back( xstart + ystart * lab.width );
	lab.xplayer = xstart;
	lab.yplayer = ystart;

	do	{
		int x = path.back() % lab.width; 
		int y = path.back() / lab.width;
		// Check neighbors
		size_t d, first;
		d = first = rand()%4;
		bool pathFound = false;
		int ineighbor, xneighbor, yneighbor;
		do	{
			xneighbor = x + dirs[d][0] * 2;
			yneighbor = y + dirs[d][1] * 2;
			ineighbor = xneighbor + yneighbor * lab.width;
			if( InBounds( lab, xneighbor, yneighbor ) &&
				lab.walls[ineighbor] == IsWall )
				{
				pathFound = true;
				break; // Found good neighbor.
				}
			d = (d+1)%4;
			}
		while( d != first );

		if( pathFound )
			{
			lab.walls[ ( x + dirs[d][0] ) + ( y + dirs[d][1] )*lab.width ] = IsPath;
			lab.walls[ (x + dirs[d][0]*2) + (y + dirs[d][1]*2)*lab.width ] = IsPath;
			path.push_back(ineighbor);
			}
		else // Backtrack!
			{
			path.pop_back();
			}
		}
	while( path.size() > 1 );

	// And tokens randomly
	for( size_t i=0; i < 10; ++i )
		lab.tokens.push_back( PlaceRandomly( lab, IsToken ) );
	}


void
MakePrettySymbols( LabData& lab )
	{
	Term::TTY tty( lab.symbuf );

	for( size_t y=0; y < lab.height; ++y )
	for( size_t x=0; x < lab.width; ++x )
		{
		if( lab.walls[ x + y * lab.width ] != IsWall ) 
			{
			tty.PlaceCursor(x,y);
			tty.Put( 176 );
			continue;
			}
		
		int neighbors = 0; // Neighbor bits.
		for( size_t d=0; d<4; ++d )
			{
			int xneighbor = x + dirs[d][0];
			int yneighbor = y + dirs[d][1];
			if( InBounds( lab, xneighbor, yneighbor ) &&
				lab.walls[ xneighbor + yneighbor*lab.width ] == IsWall )
				neighbors |= dirs[d][2]; // add bit
			}
		Term::Char::char_t c;
		switch( neighbors )
			{
			case North: case South: case North|South:
				c = 179; break;
			case East: case West: case East|West:
				c = 196; break;
			case North|East:
				c = 192 ; break;
			case North|West:
				c = 217; break;
			case South|West:
				c = 191; break;
			case South|East:
				c = 218; break;
			case North|West|South:
				c = 180; break;
			case West|North|East:
				c = 193; break;
			case West|South|East:
				c = 194; break;
			case North|East|South:
				c = 195; break;
			case North|East|South|West:
				c = 197; break;
			default:
				c = 176;
			}
		tty.PlaceCursor(x,y);
		tty.Put( c );
		}
	}


int
main( int argc, char* argv[] )
	{
	srand(2);
	LabData lab( 31, 31 );

	// Setup SDL related stuff
	SDL_Init( SDL_INIT_VIDEO );
	atexit( SDL_Quit );
	atexit( IMG_Quit );

	size_t hwin = 17;
	size_t wwin = 16;
	Term::SDL::Context term( wwin, hwin );
	term.SetTilemap( "tileset.png" );
	screen = SDL_SetVideoMode(
		term.buffer.Width() * term.GetTileWidth(),
		term.buffer.Height() * term.GetTileHeight(),
		32, SDL_SWSURFACE );
	term.SetRenderTarget( screen );
	SDL_EnableKeyRepeat( 100, 100 ); // Basically the movementspeed of the player.

	Term::TTY tty( term.buffer );
	tty.PlaceCursor( 4, lab.height/2 );
	tty.Put( "Generating labyrinth.." );
	term.Print();
	SDL_Flip(screen);

	GenerateLabyrinth( lab );
	MakePrettySymbols( lab );
	term.buffer.Copy( lab.symbuf );
	term.Print();
	SDL_Flip(screen);

	bool running = true;
	while(running)
		{
		SDL_Event event;
		while( SDL_PollEvent(&event) ) switch( event.type )
			{
			case SDL_QUIT:
				running = false; break;
			case SDL_KEYDOWN: switch( event.key.keysym.sym )
				{
				case SDLK_ESCAPE:
					running = false; break;
				case SDLK_UP:
					MovePlayer( lab, 0, -1 ); break;
				case SDLK_DOWN:
					MovePlayer( lab, 0, 1 ); break;
				case SDLK_LEFT:
					MovePlayer( lab, -1, 0 ); break;
				case SDLK_RIGHT:
					MovePlayer( lab, 1, 0 ); break;
				} break;
			}
		if( lab.win )
			{
			std::string winstr( "!!!WIN!!!" );
			int x = rand() % (term.buffer.Width()+winstr.length()) - winstr.length();
			int y = rand() % (term.buffer.Height()+winstr.length()) - winstr.length();
			tty.PlaceCursor( x,y );
			tty.SetPriColor( {
				static_cast<Term::Color::component_t>( rand() % 255 ),
				static_cast<Term::Color::component_t>( rand() % 255 ),
				static_cast<Term::Color::component_t>( rand() % 255 ) });
			tty.SetSecColor( {
				static_cast<Term::Color::component_t>( rand() % 255 ),
				static_cast<Term::Color::component_t>( rand() % 255 ),
				static_cast<Term::Color::component_t>( rand() % 255 ) });
			tty.Put( winstr );
			}
		else
			{
			term.buffer.Clear();
			term.buffer.Copy( lab.symbuf, 0, 1,
				-(term.buffer.Width()/2) + lab.xplayer, 
				-(term.buffer.Height()/2) + lab.yplayer, 
				term.buffer.Width(), term.buffer.Height() );
			tty.PlaceCursor( term.buffer.Width()/2, term.buffer.Height()/2+1 ); 
			tty.Put( 1 );
			for( auto itoken : lab.tokens )
				{
				tty.PlaceCursor( 
					(itoken % lab.width) +(term.buffer.Width())/2 - lab.xplayer ,
					(itoken / lab.width) +(term.buffer.Height()/2) - lab.yplayer +1 );
				tty.Put( 9 );
				}
			tty.PlaceCursor( 0,0 );
			if( lab.door == 0 )
				{
				tty.Put( "Tokens left: " );
				std::stringstream ss; 
				ss << lab.tokens.size();
				tty.Put( ss.str() );
				}
			else
				{
				tty.Put( "Find the door!" );
				tty.PlaceCursor( lab.door % lab.width + term.buffer.Width()/2 - lab.xplayer,
					lab.door / lab.width + term.buffer.Height()/2 + 1 - lab.yplayer );
				tty.Put( 239 );
				}
			}
		term.Print();
		SDL_Flip(screen);
		SDL_Delay(50);
		}
	}
