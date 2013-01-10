#include <iostream>
#include <fstream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <Terminate/terminate.hpp>
#include <Terminate/sdl/context.hpp>

const Term::Color BGCOLOR{ 255,200,0 };
const Term::Color FONTCOLOR{0,0,0};

int main( int argc, char* argv[] )
	{
	if( argc != 2 )
		{
		std::cerr << "Please specify an input text file as argument." << std::endl;
		}
	SDL_Init( SDL_INIT_VIDEO );
	atexit( SDL_Quit );
	atexit( IMG_Quit );

	Term::SDL::Context term( 60, 30 );
	term.SetTilemap( "tileset.png" );
	SDL_Surface* screen = SDL_SetVideoMode(
		term.buffer.Width() * term.GetTileWidth(),
		term.buffer.Height() * term.GetTileHeight(),
		32, SDL_SWSURFACE );
	term.SetRenderTarget( screen );
	term.buffer.SetClearChar( Term::Char('\0', 0, BGCOLOR, FONTCOLOR));
	term.buffer.Clear(); 


	Term::TTY tty(term.buffer);
	tty.Set( Term::TTY::VScroll );
	tty.SetPriColor( BGCOLOR );
	tty.SetSecColor( FONTCOLOR );

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
