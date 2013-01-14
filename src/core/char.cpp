/////////////////////////////////////////////
// Copyright (c) 2013 Kim Simmons
// Distributed under the Zlib/libPNG license.
// Read LICENSE.txt accompanying this source 
// for more information.
/////////////////////////////////////////////

#include "char.hpp"


namespace Term
	{

	Color Color::Black( 0,0,0 );
	Color Color::White( 255,255,255 );


	Char::Char( char_t c_, uint8_t pal,
		Color pri, Color sec) :
		c(c_),
		pal_i(pal),
		priColor(pri),
		secColor(sec)
		{}


	Char::Char( char_t c_, uint8_t pal ) :
		c(c_),
		pal_i(pal),
		priColor( Color::Black ),
		secColor( Color::White )
		{}


	Char::char_t
	Char::ASCII() const
		{
		return c;
		}


	Char&
	Char::ASCII( char_t newC )
		{
		c = newC;
		return *this;
		}


	Char&
	Char::PriColor( Color newCol )
		{
		priColor = newCol;
		return *this;
		}


	Color
	Char::PriColor() const
		{
		return priColor;
		}


	Char&
	Char::SecColor( Color newCol )
		{
		secColor = newCol;
		return *this;
		}


	Color
	Char::SecColor() const
		{
		return secColor;
		}


	} // namespace Term
