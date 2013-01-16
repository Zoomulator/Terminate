cmake_minimum_required(VERSION 2.8)
project(TERMINATE C CXX)

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g -O3" )
option( LLVMlibcxx "Use LLVMs libc++" OFF)
if( LLVMlibcxx )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++" )
    message( "Will use LLVM's libc++." )
endif( LLVMlibcxx )

add_subdirectory( src )
add_subdirectory( demo )
