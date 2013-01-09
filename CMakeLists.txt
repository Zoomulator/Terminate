cmake_minimum_required(VERSION 2.6)
project(TERMINATE CXX)


set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g -ferror-limit=5" )

include_directories( include )

add_library( Terminate
	src/char.cpp
	src/charbuffer.cpp
	src/context.cpp
	src/window.cpp
	)

add_executable( TestRun demo/run.cpp )
target_link_libraries( TestRun Terminate SDL SDLmain SDL_image )
