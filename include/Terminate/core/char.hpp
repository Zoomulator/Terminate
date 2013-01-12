/////////////////////////////////////////////
// Copyright (c) 2013 Kim Simmons
// Distributed under the Zlib/libPNG license.
// Read LICENSE.txt accompanying this source 
// for more information.
/////////////////////////////////////////////

#ifndef TERMINATE_CHAR_HPP
#define TERMINATE_CHAR_HPP


#include <cstdint>


namespace Term
	{
	typedef uint8_t char8_t;

	struct Color
		{
		uint8_t r,g,b;
		};

	class Char
		{
		public:
			Char() = default;
			Char( char8_t, uint8_t pal_i, Color, Color );
			Char( char8_t, uint8_t pal_i=0 );
			char GetChar() const;
			void SetChar( char );

			void SetPriColor( Color );
			Color GetPriColor() const;
			void SetSecColor( Color );
			Color GetSecColor() const;
		private:
			union
				{
				struct { char8_t c; uint8_t pal_i; };
				char16_t wc;
				};

			Color priColor;
			Color secColor;
		};

	} // namespace Term

#endif //TERMINATE_CHAR_HPP
