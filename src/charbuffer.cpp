#include "charbuffer.hpp"
#include <stdexcept>
#include <algorithm>

using std::max;
using std::min;

namespace Terminate
	{


	CharBuffer::CharBuffer( size_t w, size_t h ) :
		width(w), height(h),
		buffer( new Char[w*h] )
		{}


	size_t
	CharBuffer::Width() const
		{
		return width;
		}


	size_t
	CharBuffer::Height() const
		{
		return height;
		}


	void
	CharBuffer::PutChar( size_t x, size_t y, Char c )
		{
		if( x >= width || y >= height )
			return;
		//	throw std::range_error( 
		//		"CharBuffer::PutChar out of range." );

		buffer[x+y*width] = c;
		}


	Char
	CharBuffer::GetChar( size_t x, size_t y ) const
		{
		return buffer[x+y*width];
		}


	void
	CharBuffer::Copy( const CharBuffer& other, int ox, int oy )
		{
		size_t sx = max( 0, -ox );
		size_t sy = max( 0, -oy );
		size_t dx = max( 0, ox );
		size_t dy = max( 0, oy );
		for( ; sy < other.Height() && dy < Height(); ++sy, ++dy )
		for( ; sx < other.Width()  && dx < Width() ; ++sx, ++dx )
			PutChar( dx, dy, other.GetChar(sx, sy) );
		}

	} // namespace Terminate
