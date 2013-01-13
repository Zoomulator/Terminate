
include_directories( ${TERMINATE_SOURCE_DIR}/include )


option( BuildDemos "Build the Terminate demos." ON )

if( UseSDL AND BuildDemos )
	message( "Will build demos." )

	include( FindSDL )
	include( FindSDL_image )

	if( DEFINED SDL_FOUND AND DEFINED SDLIMAGE_FOUND )
		include_directories( ${SDL_INCLUDE_DIR} ${SDLIMAGE_INCLUDE_DIR} )
		unset( SDL_BUILDING_LIBRARY )
		set( SDL_LIBS ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} SDLmain )
		set( OUTPUT_DIR ${TERMINATE_SOURCE_DIR}/bin/demo )

		add_executable( TTYTest tty_test.cpp )
		target_link_libraries( TTYTest Terminate TerminateSDL ${SDL_LIBS} )
		install( TARGETS TTYTest DESTINATION ${OUTPUT_DIR} ) 

		add_executable( Maze maze.cpp )
		target_link_libraries( Maze Terminate TerminateSDL ${SDL_LIBS} )
		install( TARGETS Maze DESTINATION ${OUTPUT_DIR} )

		add_executable( Marquee marquee.cpp )
		target_link_libraries( Marquee Terminate TerminateSDL ${SDL_LIBS} )
		install( TARGETS Marquee DESTINATION ${OUTPUT_DIR} ) 

		add_executable( PrintFile printfile.cpp )
		target_link_libraries( PrintFile Terminate TerminateSDL ${SDL_LIBS} )
		install( TARGETS PrintFile DESTINATION ${OUTPUT_DIR} ) 

		install(FILES "../tileset.png" DESTINATION ${OUTPUT_DIR})
	elseif( NOT DEFINED SDL_FOUND )
		message( ERROR "SDL not found!" )
	else()
		message( ERROR "SDL_image not found!" )
	endif()
elseif( NOT UseSDL )
	message( "-NO DEMOS- will be built. Depends on SDL." )
elseif( NOT BuildDemos )
	message( "-NO DEMOS- will be built." )
endif( UseSDL AND BuildDemos )
