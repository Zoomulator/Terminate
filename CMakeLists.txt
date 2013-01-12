cmake_minimum_required(VERSION 2.6)
project(TERMINATE CXX)


if( ${CMAKE_SYSTEM_NAME} MATCHES Linux )
	set( CMAKE_INSTALL_PREFIX /bin/ )
endif()
message( "Installs libraries to ${CMAKE_INSTALL_PREFIX}")

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g -O3 -ferror-limit=5" )
option( LLVMlibcxx "Use LLVMs libc++" OFF)
if( LLVMlibcxx )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++" )
	message( "Will use LLVM's libc++." )
endif( LLVMlibcxx )

add_subdirectory( src )
add_subdirectory( demo )
