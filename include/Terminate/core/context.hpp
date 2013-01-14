/////////////////////////////////////////////
// Copyright (c) 2013 Kim Simmons
// Distributed under the Zlib/libPNG license.
// Read LICENSE.txt accompanying this source 
// for more information.
/////////////////////////////////////////////

#ifndef TERMINATE_CONTEXT_HPP
#define TERMINATE_CONTEXT_HPP

#include <string>
#include "buffer.hpp"

namespace Term
	{

	typedef int TileCount;
	typedef int TileSize;
	typedef int PixDim;


	class Context
		{
		public:
			Buffer buffer;

			Context( size_t width, size_t height ) : buffer(width,height) {}
			virtual ~Context() {}
			virtual void Print() const = 0;
			virtual void Print( Char ch, size_t x, size_t y ) const = 0;
		};

	} // namespace Term

#endif //TERMINATE_CONTEXT_HPP
