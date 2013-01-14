#include <fstream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <Terminate/terminate.hpp>
#include <Terminate/sdl/context.hpp>

const Term::Color BGCOLOR( 255,200,0 );
const Term::Color FONTCOLOR(0,0,0);

int
main( int argc, char* argv[] )
	{
	SDL_Init( SDL_INIT_VIDEO );
	atexit( SDL_Quit );
	atexit( IMG_Quit );

	Term::SDL::Context term( 60, 30 );
	term.Tilemap( "tileset.png" );
	SDL_Surface* screen = SDL_SetVideoMode(
		term.buffer.Width()  * term.TileWidth(),
		term.buffer.Height() * term.TileHeight(),
		32, SDL_SWSURFACE );
	term.RenderTarget( screen );
	term.buffer.ClearChar( Term::Char('\0').PriColor(BGCOLOR).SecColor(Term::Color::Black) );
	term.buffer.Clear(); 


	using Term::TTY;
	TTY tty(term.buffer);
	tty.Set( TTY::VScroll ).PriColor( BGCOLOR ).SecColor( FONTCOLOR );

	if( argc != 2 )
		{
		tty.Place( 4, term.buffer.Height()/2 );
		tty.Put( "Usage: Specify a textfile as a command line argument." );
		}

	std::ifstream file( argv[1] );

	bool running = true;
	while(running)
		{
		SDL_Event event;
		while( SDL_PollEvent(&event) ) switch(event.type)
			{
			case SDL_QUIT:
			case SDL_KEYDOWN:
				running = false; break;
			}

		if( file.good() )
			{
			char c;
			file.get(c);
			tty.Put(c);
			}

		term.Print();
		SDL_Flip(screen);
		SDL_Delay(5);
		}
	}
