#include <iostream>
#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <functional>
#include <terminate.hpp>


SDL_Surface* screen;

int main( int argc, char* argv[] )
	{
	SDL_Init( SDL_INIT_VIDEO );
	IMG_Init( IMG_INIT_PNG );
	atexit(SDL_Quit);
	atexit(IMG_Quit);
	Terminate::Context term;
	term.SetTilemap( "tiles2.png" );
	Terminate::Window win(term, 20, 15);
	screen = SDL_SetVideoMode( 
		win.GetWindowPixWidth(),
		win.GetWindowPixHeight(),
		32, SDL_SWSURFACE );
	std::string hello("Hello, terminal!");
	Terminate::Char ch;
	ch.SetPriColor( {0,0,0,255} );
	ch.SetSecColor( {0,255,0,255} );

	for( size_t i=0; i<hello.length(); ++i )
		{
		ch.SetChar( hello[i] );
		ch.SetPriColor( { 
			static_cast<Uint8>(rand()%255),
			static_cast<Uint8>(rand()%255),
			static_cast<Uint8>(rand()%255),
			255 } );
		ch.SetSecColor( {
			static_cast<Uint8>(rand()%255),
			static_cast<Uint8>(rand()%255),
			static_cast<Uint8>(rand()%255),
			255 } );
		win.PutChar( i, 0, ch );
		win.Render(screen);
		SDL_Flip(screen);
		SDL_Delay(250);
		}
	win.Render(screen);
	SDL_Flip(screen);
	bool running = true;
	while( running )
		{
		SDL_Event event;
		while( SDL_PollEvent(&event) ) switch( event.type )
			{
			case SDL_QUIT:
			case SDL_KEYDOWN:
				running=false; break;
			}
		}

	return 0;
	}
