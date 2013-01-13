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

	struct Color
		{
		uint8_t r,g,b;
		};

	class Char
		{
		public:
			typedef uint8_t char_t;
			Char() = default;
			Char( char_t, uint8_t pal_i, Color, Color );
			Char( char_t, uint8_t pal_i=0 );
			char_t GetChar() const;
			void SetChar( char_t );

			void SetPriColor( Color );
			Color GetPriColor() const;
			void SetSecColor( Color );
			Color GetSecColor() const;
		private:
			union
				{
				struct { char_t c; uint8_t pal_i; };
				char16_t wc;
				};

			Color priColor;
			Color secColor;
		};

	} // namespace Term

#endif //TERMINATE_CHAR_HPP
