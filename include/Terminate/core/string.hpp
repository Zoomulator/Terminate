/////////////////////////////////////////////
// Copyright (c) 2013 Kim Simmons
// Distributed under the Zlib/libPNG license.
// Read LICENSE.txt accompanying this source 
// for more information.
/////////////////////////////////////////////

#ifndef TERMINATE_STRING_HPP
#define TERMINATE_STRING_HPP

#include <string>
#include "char.hpp"

namespace Term
	{

	struct Term_char_traits : public std::char_traits<Char>
		{

		typedef Char char_type;

		static bool eq( Char a, Char b )
			{
			return a.ASCII() == b.ASCII();
			}

		static bool lt( Char a, Char b )
			{
			return a.ASCII() < b.ASCII();
			}

		static bool compare( const Char* a, const Char* b, size_t n )
			{
			while( n-- != 0 )
				{
				if( a[n].ASCII() < b[n].ASCII() ) return -1;
				if( a[n].ASCII() > b[n].ASCII() ) return 1;
				++a; ++b;
				}
			return 0;
			}
		};

	typedef std::basic_string<Char,Term_char_traits> String;

	String MakeString( const std::string& );
	void PriColor( String&, Color );
	void SecColor( String&, Color );


	} // namespace Term
#endif //TERMINATE_STRING_HPP
