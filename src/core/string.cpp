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
			ch.ASCII(c);
			termstr.push_back( ch );
			}
		return termstr;
		}


	void
	PriColor( String& str, Color color )
		{
		for( auto& ch : str )
			ch.PriColor( color );
		}


	void
	SecColor( String& str, Color color )
		{
		for( auto& ch : str )
			ch.SecColor( color );
		}


	} // namespace Term
