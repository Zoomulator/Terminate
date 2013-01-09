#include "string.hpp"

namespace Terminate
	{


	String MakeString( const std::string& str )
		{
		String termstr;
		termstr.reserve( str.length() );
		Char ch;
		for( auto c : str )
			{
			ch.SetChar(c);
			termstr.push_back( ch );
			}
		return termstr;
		}


	void
	SetPriColor( String& str, Color color )
		{
		for( auto& ch : str )
			ch.SetPriColor( color );
		}


	void
	SetSecColor( String& str, Color color )
		{
		for( auto& ch : str )
			ch.SetSecColor( color );
		}


	} // namespace Terminate
