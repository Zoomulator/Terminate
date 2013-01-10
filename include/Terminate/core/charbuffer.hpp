/////////////////////////////////////////////
// Copyright (c) 2013 Kim Simmons
// Distributed under the Zlib/libPNG license.
// Read LICENSE.txt accompanying this source 
// for more information.
/////////////////////////////////////////////

#ifndef TERMINATE_CHARBUFFER_HPP
#define TERMINATE_CHARBUFFER_HPP

#include <cstdlib>
#include <memory>
#include "char.hpp"


namespace Term
	{

	
	class CharBuffer
		{
		public:
			CharBuffer( size_t width, size_t height );
			size_t Width() const;
			size_t Height() const;
			void Clear(); 
			void SetClearChar( Char );
			void Put( size_t x, size_t y, Char );
			Char Get( size_t x, size_t y ) const;
			void Scroll( int rows, int cols=0);
			void Copy( const CharBuffer&, int dx, int dy, 
				size_t sx, size_t sy, size_t sw, size_t sh );
			void Copy( const CharBuffer& );

		private:
			size_t width, height;
			Char clearChar;
			std::unique_ptr<Char[]> buffer;
		};


	} // namespace Term

#endif //TERMINATE_CHARBUFFER_HPP
