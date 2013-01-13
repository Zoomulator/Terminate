#include <iostream>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <Terminate/terminate.hpp>
#include <Terminate/sdl/context.hpp>

// Possible movement. Each direction has dx,dy and a flag bit
const int dirs[4][2] = { {0,-1}, {1,0}, {0,1}, {-1,0} };
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
			std::cout << "(" << xneighbor << ":" << yneighbor << ")-> " << std::endl; 
			}
		else // Backtrack!
			{
			path.pop_back();
			std::cout << "<- ";
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
	tty.PlaceCursor(0,0);
	tty.Set( Term::TTY::Wrap );
	for( auto wall : lab.walls )
		if( wall == IsWall )
			tty.Put( 254 );
		else
			tty.Put( 176 );

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
