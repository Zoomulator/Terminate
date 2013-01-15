include_directories(${TERMINATE_SOURCE_DIR}/include/Terminate/core)
file( GLOB_RECURSE CORE_SOURCE_FILES *.cpp )
add_library( Terminate SHARED ${CORE_SOURCE_FILES} )
add_library( Terminate_static STATIC ${CORE_SOURCE_FILES} )
set_target_properties( Terminate Terminate_static
    PROPERTIES
     SOVERSION 1
     VERSION 1.1.0
    )

install( TARGETS Terminate Terminate_static
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib )
