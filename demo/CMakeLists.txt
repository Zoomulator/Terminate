
include_directories( ${TERMINATE_SOURCE_DIR}/include )


option( BuildDemos "Build the Terminate demos." ON )

if( UseSDL AND BuildDemos )
	message( "Will build demos." )
	set( OUTPUT_DIR ${TERMINATE_SOURCE_DIR}/bin/demo )
	add_executable( TTYTest tty_test.cpp )
	target_link_libraries( TTYTest Terminate TerminateSDL SDL SDLmain SDL_image )
	install( TARGETS TTYTest DESTINATION ${OUTPUT_DIR} ) 

	add_executable( Marquee marquee.cpp )
	target_link_libraries( Marquee Terminate TerminateSDL SDL SDLmain SDL_image )
	install( TARGETS Marquee DESTINATION ${OUTPUT_DIR} ) 

	add_executable( PrintFile printfile.cpp )
	target_link_libraries( PrintFile Terminate TerminateSDL SDL SDLmain SDL_image )
	install( TARGETS PrintFile DESTINATION ${OUTPUT_DIR} ) 
elseif( NOT UseSDL )
	message( "-NO DEMOS- will be built. Depends on SDL." )
elseif( NOT BuildDemos )
	message( "-NO DEMOS- will be built." )
endif( UseSDL AND BuildDemos )
