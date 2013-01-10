
include_directories( ${TERMINATE_SOURCE_DIR}/include )

add_executable( TTYTest tty_test.cpp )
target_link_libraries( TTYTest Terminate TerminateSDL SDL SDLmain SDL_image )

add_executable( Marquee marquee.cpp )
target_link_libraries( Marquee Terminate TerminateSDL SDL SDLmain SDL_image )

add_executable( PrintFile printfile.cpp )
target_link_libraries( PrintFile Terminate TerminateSDL SDL SDLmain SDL_image )
