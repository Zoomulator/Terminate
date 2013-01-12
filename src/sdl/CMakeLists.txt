include_directories( ${TERMINATE_SOURCE_DIR}/include/Terminate )

set(TERMSDL_SOURCE_FILES context.cpp)

option( UseSDL "Build stuff with SDL dependency." ON )


if( UseSDL )
	message( "Will build SDL context library TerminateSDL" )

	add_library( TerminateSDL SHARED ${TERMSDL_SOURCE_FILES} )
	add_library( TerminateSDL_static STATIC ${TERMSDL_SOURCE_FILES} )

	set_target_properties( TerminateSDL TerminateSDL_static
		PROPERTIES
		 SOVERSION 0
		 VERSIO 1.0.0
		)

	install( TARGETS TerminateSDL TerminateSDL_static
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib )
else( UseSDL )
	message( "Will -NOT- build SDL context library TerminateSDL" )
endif( UseSDL )
