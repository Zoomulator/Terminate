#include "char.hpp"


namespace Terminate
	{


	Char::Char() :
		c('\0'),
		priColor{255,255,255,255},
		secColor{0,0,0,255}
		{}


	char
	Char::GetChar() const
		{
		return c;
		}


	void
	Char::SetChar( char newC )
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


	} // namespace Terminate
