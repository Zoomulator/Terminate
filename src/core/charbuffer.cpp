/////////////////////////////////////////////
// Copyright (c) 2013 Kim Simmons
// Distributed under the Zlib/libPNG license.
// Read LICENSE.txt accompanying this source 
// for more information.
/////////////////////////////////////////////

#include "charbuffer.hpp"
#include <stdexcept>
#include <algorithm>

using std::max;
using std::min;

namespace Term
	{


	CharBuffer::CharBuffer( size_t w, size_t h ) :
		width(w), height(h),
		clearChar( '\0' ),
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
	CharBuffer::Clear()
		{
		size_t size = width*height;
		for(size_t i=0; i < size; ++i )
			buffer[i] = clearChar;
		}


	void
	CharBuffer::SetClearChar( Char ch )
		{
		clearChar = ch;
		}


	void
	CharBuffer::Put( size_t x, size_t y, Char c )
		{
		if( x >= width || y >= height )
			return;
		//	throw std::range_error( 
		//		"CharBuffer::PutChar out of range." );

		buffer[x+y*width] = c;
		}


	Char
	CharBuffer::Get( size_t x, size_t y ) const
		{
		if( x < width && y < height )
			return buffer[x+y*width];
		else
			return Char();
		}


	void
	CharBuffer::Scroll( int rows, int cols )
		{
		CharBuffer tmpBuf(Width(),Height());
		tmpBuf.SetClearChar( clearChar );
		tmpBuf.Clear();
		tmpBuf.Copy( *this, -cols, -rows, 0,0, Width(), Height() );
		*this = std::move(tmpBuf);
		}


	void
	CharBuffer::Copy( const CharBuffer& other, int dx, int dy,
		size_t sx, size_t sy, size_t sw, size_t sh )
		{
		for( size_t y=0; y < sh; ++y )
		for( size_t x=0; x < sw; ++x )
			{
			Put( dx+x, dy+y, other.Get(sx+x,sy+y) );
			}
		}


	void
	CharBuffer::Copy( const CharBuffer& other )
		{
		Copy( other, 0,0, 0,0, min(Width(),other.Width()), min(Height(),other.Height()) );
		}

	} // namespace Term
