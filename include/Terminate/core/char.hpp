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
	typedef uint8_t uchar8_t;

	struct Color
		{
		uint8_t r,g,b;
		};

	class Char
		{
		public:
			Char() = default;
			Char( uchar8_t, uint8_t pal_i, Color, Color );
			Char( uchar8_t, uint8_t pal_i=0 );
			uchar8_t GetChar() const;
			void SetChar( uchar8_t );

			void SetPriColor( Color );
			Color GetPriColor() const;
			void SetSecColor( Color );
			Color GetSecColor() const;
		private:
			union
				{
				struct { uchar8_t c; uint8_t pal_i; };
				char16_t wc;
				};

			Color priColor;
			Color secColor;
		};

	} // namespace Term

#endif //TERMINATE_CHAR_HPP
