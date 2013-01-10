/////////////////////////////////////////////
// Copyright (c) 2013 Kim Simmons
// Distributed under the Zlib/libPNG license.
// Read LICENSE.txt accompanying this source 
// for more information.
/////////////////////////////////////////////

#include "tty.hpp"



namespace Term
	{
	

	TTY::TTY( CharBuffer& buf ) :
		buffer(&buf),
		curs_x(0), curs_y(0),
		state(0),
		pri{ 255,255,255 },
		sec{ 0,0,0 }
		{}


	void
	TTY::Set( StateBit b, bool setTo )
		{
		if( setTo )
			state |= b;
		else
			state ^= b;
		}


	bool
	TTY::IsSet( StateBit b ) const
		{
		return (b & state) == b; 
		}


	void
	TTY::PlaceCursor( size_t x, size_t y )
		{
		if( IsSet(Wrap) && x >= buffer->Width() )
			{
			++y;
			x %= buffer->Width();
			}

		if( IsSet(VScroll) && y >= buffer->Height() )
			{
			buffer->Scroll( y - buffer->Height() + 1 );
			y = buffer->Height() - 1;
			}
		curs_x = x;
		curs_y = y;
		}


	void
	TTY::ClearLine()
		{
		for( size_t x=0; x<buffer->Width(); ++x )
			buffer->Put(x,curs_y, Char() );

		PlaceCursor(0,curs_y);
		}


	Char
	TTY::Get() const
		{
		return buffer->Get(curs_x,curs_y);
		}


	void
	TTY::Put( Char ch )
		{
		if( IsSet(Insert) &&
			Get().GetChar() != '\0' )
			{
			TTY insert(*buffer);
			insert.PlaceCursor(curs_x+1, curs_y);
			Char next = Get();
			do  {
				Char tmp = insert.Get();
				insert.Put(next);
				next = tmp;
				}
			while( next.GetChar() != '\0' );
			}

		if( ch.GetChar() == '\n' )
			PlaceCursor( 0, curs_y + 1 );
		else
			{
			buffer->Put( curs_x, curs_y, ch );
			PlaceCursor( curs_x + 1, curs_y );
			}
		}


	void
	TTY::Put( const String& str )
		{
		for( Char ch : str )
			Put(ch);
		}



	void
	TTY::Put( char c )
		{
		Char ch;
		ch.SetChar(c);
		ch.SetPriColor(pri);
		ch.SetSecColor(sec);
		Put(ch);
		}


	void
	TTY::Put( const std::string& str )
		{
		for( auto c : str )
			Put(c);
		}


	void
	TTY::SetPriColor( Color color )
		{
		pri = color;
		}


	void
	TTY::SetSecColor( Color color )
		{
		sec = color;
		}


	} // namespace Term
