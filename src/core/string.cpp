/////////////////////////////////////////////
// Copyright (c) 2013 Kim Simmons
// Distributed under the Zlib/libPNG license.
// Read LICENSE.txt accompanying this source 
// for more information.
/////////////////////////////////////////////

#include "string.hpp"

namespace Term
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


	} // namespace Term
