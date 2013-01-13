/////////////////////////////////////////////
// Copyright (c) 2013 Kim Simmons
// Distributed under the Zlib/libPNG license.
// Read LICENSE.txt accompanying this source 
// for more information.
/////////////////////////////////////////////

#include "char.hpp"


namespace Term
	{


	Char::Char( uchar8_t c_, uint8_t pal,
		Color pri, Color sec) :
		c(c_),
		pal_i(pal),
		priColor(pri),
		secColor(sec)
		{}


	Char::Char( uchar8_t c_, uint8_t pal ) :
		c(c_),
		pal_i(pal),
		priColor{255,255,255},
		secColor{0,0,0}
		{}


	uchar8_t
	Char::GetChar() const
		{
		return c;
		}


	void
	Char::SetChar( uchar8_t newC )
		{
		c = newC;
		}


	void
	Char::SetPriColor( Color newCol )
		{
		priColor = newCol;
		}


	Color
	Char::GetPriColor() const
		{
		return priColor;
		}


	void
	Char::SetSecColor( Color newCol )
		{
		secColor = newCol;
		}


	Color
	Char::GetSecColor() const
		{
		return secColor;
		}


	} // namespace Term
