cmake_minimum_required(VERSION 2.6)
project(TERMINATE CXX)


set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g -ferror-limit=5" )
add_subdirectory( src )
add_subdirectory( demo )
