#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <Terminate/terminate.hpp>
#include <Terminate/sdl/context.hpp>


Term::Color
RandomColor()
    {
    return Term::Color (
        static_cast<Uint8>(rand()%255),
        static_cast<Uint8>(rand()%255),
        static_cast<Uint8>(rand()%255) );
    }


void
RandomColors( Term::String& str )
    {
    for( Term::Char& ch : str )
        ch.PriColor( Term::Color::Black ).SecColor( RandomColor() );
    }


int
main( int argc, char* argv[] )
    {
    // Setup SDL and our terminal buffer.
    SDL_Init( SDL_INIT_VIDEO );

    atexit( SDL_Quit );
    atexit( IMG_Quit );
    Term::SDL::Context term( 20, 3 );
    term.Tilemap( "tileset.png" );

    SDL_Surface* screen = SDL_SetVideoMode(
        term.buffer.Width()  * term.TileWidth(),
        term.buffer.Height() * term.TileHeight(),
        32, SDL_SWSURFACE );
    term.RenderTarget(screen);

    // Prepare the marquee!
    Term::String bannerText = Term::MakeString( "Terminate Terminal emulator running SDL" );
    Term::Buffer banner( bannerText.length(), 1 );
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
        tty.Place( 0, 0 );
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
