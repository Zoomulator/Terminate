#include <iostream>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <Terminate/terminate.hpp>
#include <Terminate/sdl/context.hpp>

// Possible movement. Each direction has dx,dy and a flag bit
enum { North=1, East=2, South=4, West=8 };
const int dirs[4][3] = { {0,-1,North}, {1,0,East}, {0,1,South}, {-1,0,West} };
enum { IsWall=0, IsPath };

SDL_Surface* screen;
Term::SDL::Context* p_term;

struct
LabData
	{
	typedef std::vector<Uint8> WallData;
	typedef std::vector<Uint32> TokenData;
	Uint8 width, height;
	WallData walls;
	TokenData tokens;
	};


void
GenerateLabyrinth( LabData& lab )
	{
	Term::TTY tty( p_term->buffer );
	size_t labSize = lab.width * lab.height;
	lab.walls.resize( labSize, IsWall );
	std::vector<Uint32> path; // Stack for backtracking. 
	int xstart = rand() % lab.width;
	int ystart = rand() % lab.height;
	xstart += xstart%2 ? 0 : 1;
	ystart += ystart%2 ? 0 : 1; // Start on even coordinate.
	path.push_back( xstart + ystart * lab.width );

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
			if( xneighbor < lab.width  && xneighbor >= 0 &&
				yneighbor < lab.height && yneighbor >= 0 &&
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
	}


int
main( int argc, char* argv[] )
	{
	LabData lab{ 51, 51 };

	// Setup SDL related stuff
	SDL_Init( SDL_INIT_VIDEO );
	atexit( SDL_Quit );
	atexit( IMG_Quit );

	Term::SDL::Context term( lab.width, lab.height );
	p_term = &term;
	term.SetTilemap( "tileset.png" );
	screen = SDL_SetVideoMode(
		term.buffer.Width() * term.GetTileWidth(),
		term.buffer.Height() * term.GetTileHeight(),
		32, SDL_SWSURFACE );
	term.SetRenderTarget( screen );

	Term::TTY tty( term.buffer );
	tty.PlaceCursor( 4, lab.height/2 );
	tty.Put( "Generating labyrinth.." );
	term.Print();
	SDL_Flip(screen);

	GenerateLabyrinth( lab );
	for( size_t y=0; y < lab.height; ++y )
	for( size_t x=0; x < lab.width; ++x )
		{
		if( lab.walls[ x + y * lab.width ] == IsPath ) 
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
			if( xneighbor < lab.width  && xneighbor >= 0 &&
				yneighbor < lab.height && yneighbor >= 0 &&
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
				} break;
			}
		}
	}
