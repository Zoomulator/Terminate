#include "tty.hpp"



namespace Term
	{
	

	TTY::TTY( CharBuffer& buf ) :
		buffer(&buf),
		curs_x(0), curs_y(0)
		{}


	void
	TTY::PlaceCursor( size_t x, size_t y )
		{
		if( state & Wrap && x >= buffer->Width() )
			{
			++y;
			x %= buffer->Width();
			}

		curs_x = x;
		curs_y = y;
		}


	void
	TTY::Put( Char ch )
		{
		if( ch.GetChar() == '\n' )
			PlaceCursor( 0, curs_y + 1 );
		else
			{
			buffer->PutChar( curs_x, curs_y, ch );
			PlaceCursor( curs_x + 1, curs_y );
			}
		}


	void
	TTY::Put( const String& str )
		{
		for( auto ch : str )
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
