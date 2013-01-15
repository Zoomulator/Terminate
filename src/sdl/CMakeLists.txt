include_directories( ${TERMINATE_SOURCE_DIR}/include/Terminate )

set(TERMSDL_SOURCE_FILES context.cpp)

option( UseSDL "Build stuff with SDL dependency." ON )


if( UseSDL )
    message( "Will build SDL context library TerminateSDL" )

    include( FindSDL )
    include( FindSDL_image )

    if( DEFINED SDL_FOUND AND DEFINED SDLIMAGE_FOUND )
        include_directories( ${SDL_INCLUDE_DIR} ${SDLIMAGE_INCLUDE_DIR} )
#        set( SDL_BUILDING_LIBRARY YES )
        add_library( TerminateSDL SHARED ${TERMSDL_SOURCE_FILES} )
        target_link_libraries( TerminateSDL Terminate ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} )

        add_library( TerminateSDL_static STATIC ${TERMSDL_SOURCE_FILES} )
        target_link_libraries( TerminateSDL_static Terminate_static ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} )

        set_target_properties( TerminateSDL TerminateSDL_static
            PROPERTIES
             SOVERSION 1
             VERSIO 1.1.0
            )

        install( TARGETS TerminateSDL TerminateSDL_static
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib )
    elseif( NOT DEFINED SDL_FOUND )
        message( ERROR "SDL was not found." )
    else()
        message( ERROR "SDL_image was not found." )
    endif()
else( UseSDL )
    message( "Will -NOT- build SDL context library TerminateSDL" )
endif( UseSDL )
