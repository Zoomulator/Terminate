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
			return a.GetChar() == b.GetChar();
			}

		static bool lt( Char a, Char b )
			{
			return a.GetChar() < b.GetChar();
			}

		static bool compare( const Char* a, const Char* b, size_t n )
			{
			while( n-- != 0 )
				{
				if( a[n].GetChar() < b[n].GetChar() ) return -1;
				if( a[n].GetChar() > b[n].GetChar() ) return 1;
				++a; ++b;
				}
			return 0;
			}
		};

	typedef std::basic_string<Char,Term_char_traits> String;

	String MakeString( const std::string& );
	void SetPriColor( String&, Color );
	void SetSecColor( String&, Color );


	} // namespace Term
#endif //TERMINATE_STRING_HPP
