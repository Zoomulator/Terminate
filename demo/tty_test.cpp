#include <cstdlib>
#include <sstream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <Terminate/terminate.hpp>
#include <Terminate/sdl/context.hpp>


SDL_Surface* screen;

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
	SDL_Init( SDL_INIT_VIDEO );
	atexit(SDL_Quit);
	atexit(IMG_Quit);

	Term::SDL::Context term( 20, 15 );
	term.SetTilemap( "tileset.png" );
	term.buffer.Clear();
	Term::TTY tty( term.buffer );

	screen = SDL_SetVideoMode( 
		term.buffer.Width() * term.GetTileWidth(),
		term.buffer.Height() * term.GetTileHeight(),
		32, SDL_SWSURFACE );
	term.SetRenderTarget( screen );

	Term::String hello = Term::MakeString("Hello, terminal!");
	Term::String wrapStr = Term::MakeString( "Wraaaaaaaap" );
	Term::String newLineStr = Term::MakeString( "Eeeey, I'll change line\nNewline!" );
	RandomColors(hello);
	RandomColors(wrapStr);

	for( Term::Char c : hello )
		{
		tty.Put( c );
		term.Print();
		SDL_Flip(screen);
		SDL_Delay(50);
		}
	tty.Set( Term::TTY::Wrap );
	tty.SetPriColor( { 255,200,0 } );
	tty.SetSecColor( { 0,0,0 } );
	tty.PlaceCursor( 15, 7 );
	tty.Put(wrapStr);
	tty.PlaceCursor( 0, 3 );
	tty.Put( "Done!" );
	tty.PlaceCursor( 6, 10 );
	tty.Put( newLineStr );
	tty.PlaceCursor( 0, 11 );
	tty.Put( "This  Term" );
	tty.Set( Term::TTY::Insert );
	tty.PlaceCursor( 5, 11 );
	tty.Put( "is" );
	std::stringstream ss;
	ss << "Char size: " << sizeof(Term::Char);
	tty.PlaceCursor( 0, 14 );
	tty.Put( ss.str() );

	tty.PlaceCursor(0,2);
	for( int i=0; i < 20; ++i )
		tty.Put( (char) i+127 );	

	term.Print();
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
