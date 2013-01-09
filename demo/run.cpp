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
	atexit(SDL_Quit);
	atexit(IMG_Quit);
	Term::Context term;
	term.SetTilemap( "tiles2.png" );
	Term::Window win(term, 20, 15);
	Term::TTY tty( win.GetBuffer() );
	screen = SDL_SetVideoMode( 
		win.GetWindowPixWidth(),
		win.GetWindowPixHeight(),
		32, SDL_SWSURFACE );
	std::string hello("Hello, terminal!");
	for( char& c : hello )
		{
		tty.SetPriColor( { 
			static_cast<Uint8>(rand()%255),
			static_cast<Uint8>(rand()%255),
			static_cast<Uint8>(rand()%255),
			255 } );
		tty.SetSecColor( {
			static_cast<Uint8>(rand()%255),
			static_cast<Uint8>(rand()%255),
			static_cast<Uint8>(rand()%255),
			255 } );
		tty.Put( c );
		win.Render(screen);
		SDL_Flip(screen);
		SDL_Delay(50);
		}
	tty.SetPriColor( { 255,200,0,255 } );
	tty.SetSecColor( { 0,0,0,255 } );
	tty.PlaceCursor( 0, 3 );
	tty.Put( "Done!" );

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
