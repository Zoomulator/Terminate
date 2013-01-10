#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <Terminate/terminate.hpp>
#include <Terminate/sdl/context.hpp>


void RandomColors( Term::String& str )
	{
	for( Term::Char& ch : str )
		{
		ch.SetPriColor( { 
			static_cast<Uint8>(rand()%255),
			static_cast<Uint8>(rand()%255),
			static_cast<Uint8>(rand()%255) } );
		ch.SetSecColor( {
			static_cast<Uint8>(rand()%255),
			static_cast<Uint8>(rand()%255),
			static_cast<Uint8>(rand()%255) } );
		}
	}


int main( int argc, char* argv[] )
	{
	// Setup SDL and our terminal buffer.
	SDL_Init( SDL_INIT_VIDEO );

	atexit( SDL_Quit );
	atexit( IMG_Quit );
	Term::SDL::Context term( 20, 3 );
	term.SetTilemap( "tileset.png" );

	SDL_Surface* screen = SDL_SetVideoMode(
		term.buffer.Width() * term.GetTileWidth(),
		term.buffer.Height() * term.GetTileHeight(),
		32, SDL_SWSURFACE );
	term.SetRenderTarget(screen);

	// Prepare the marquee!
	Term::String bannerText = Term::MakeString( "Terminate Terminal emulator running SDL" );
	Term::CharBuffer banner( bannerText.length(), 1 );
	Term::TTY tty(banner);
		
	// Offset used to make the text move.
	int offset = term.buffer.Width();
	bool running=true;
	while(running)
		{
		SDL_Event event;
		while( SDL_PollEvent(&event) ) switch( event.type )
			{
			case SDL_QUIT:
			case SDL_KEYDOWN:
				running = false; break;
			}

		// Print some utterly unreadable randomly colored text.
		tty.PlaceCursor( 0, 0 );
		RandomColors(bannerText);
		tty.Put( bannerText );
		term.buffer.Clear();
		term.buffer.Copy( banner, offset, 1, 0,0,banner.Width(),banner.Height() );
		term.Print();
		SDL_Flip(screen);
		SDL_Delay(50);
		// Move text and wrap around screen.
		if( --offset < -(int)banner.Width() )
			offset = term.buffer.Width();
		}
	}
