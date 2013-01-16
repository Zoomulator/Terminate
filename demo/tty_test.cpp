#include <cstdlib>
#include <sstream>
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
    SDL_Init( SDL_INIT_VIDEO );
    atexit(SDL_Quit);
    atexit(IMG_Quit);

    Term::SDL::Context term( 48, 15 );
    term.Tilemap( "tileset.png" );
    term.Framebuffer().Clear();
    Term::TTY tty( term.Framebuffer() );

    SDL_Surface* screen = SDL_SetVideoMode(
        term.Framebuffer().Width()  * term.TileWidth(),
        term.Framebuffer().Height() * term.TileHeight(),
        32, SDL_SWSURFACE );
    term.RenderTarget( screen );

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

    using Term::TTY;
    tty.Set( TTY::Wrap ).PriColor( Term::Color(255,200,0) ).SecColor( Term::Color(0,0,0) );
    tty.Place( 15,7 ).Put( wrapStr );
    tty.Place( 0, 3 ).Put( "Done!" );
    tty.Place( 6,10 ).Put( newLineStr );
    tty.Place( 0,11 ).Put( "Insert between angles ><" );
    tty.Set( TTY::Insert ).Place( 23, 11 ).Put( "!inserted!" );
    std::stringstream ss;
    ss << "Char size: " << sizeof(Term::Char);
    tty.Place( 0,14 ).Put( ss.str() );
    tty.Place(0,2);
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
