/////////////////////////////////////////////
// Copyright (c) 2013 Kim Simmons
// Distributed under the Zlib/libPNG license.
// Read LICENSE.txt accompanying this source 
// for more information.
/////////////////////////////////////////////

#include "buffer.hpp"
#include <stdexcept>
#include <algorithm>

using std::max;
using std::min;

namespace Term
	{


	Buffer::Buffer( size_t w, size_t h ) :
		width(w), height(h),
		clearChar( '\0' ),
		buffer( new Char[w*h] )
		{}


	size_t
	Buffer::Width() const
		{
		return width;
		}


	size_t
	Buffer::Height() const
		{
		return height;
		}


	void
	Buffer::Clear()
		{
		size_t size = width*height;
		for(size_t i=0; i < size; ++i )
			buffer[i] = clearChar;
		}


	void
	Buffer::ClearChar( Char ch )
		{
		clearChar = ch;
		}


	void
	Buffer::Put( size_t x, size_t y, Char c )
		{
		if( x >= width || y >= height )
			return;
		//	throw std::range_error( 
		//		"Buffer::PutChar out of range." );

		buffer[x+y*width] = c;
		}


	Char
	Buffer::Get( size_t x, size_t y ) const
		{
		if( x < width && y < height )
			return buffer[x+y*width];
		else
			return Char();
		}


	void
	Buffer::Scroll( int rows, int cols )
		{
		Buffer tmpBuf(Width(),Height());
		tmpBuf.ClearChar( clearChar );
		tmpBuf.Clear();
		tmpBuf.Copy( *this, -cols, -rows, 0,0, Width(), Height() );
		*this = std::move(tmpBuf);
		}


	void
	Buffer::Copy( const Buffer& other, int dx, int dy,
		int sx, int sy, size_t sw, size_t sh )
		{
		sh = min( sh, other.Height() - sy );
		sw = min( sw, other.Width() - sx );
		for( size_t y=max(-sy,0); y < sh; ++y )
		for( size_t x=max(-sx,0); x < sw; ++x )
			{
			Put( dx+x, dy+y, other.Get(sx+x,sy+y) );
			}
		}


	void
	Buffer::Copy( const Buffer& other )
		{
		Copy( other, 0,0, 0,0, min(Width(),other.Width()), min(Height(),other.Height()) );
		}

	} // namespace Term
