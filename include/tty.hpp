#ifndef TERMINATE_TTY_HPP
#define TERMINATE_TTY_HPP

#include "charbuffer.hpp"
#include "string.hpp"

namespace Term
	{

	class TTY
		{
		public:
			enum : unsigned int { Wrap=1 };
			TTY( CharBuffer& );
			void PlaceCursor( size_t x, size_t y );
			void Put( Char );
			void Put( const String& );
			void Put( char );
			void Put( const std::string& );
			void SetPriColor( Color );
			void SetSecColor( Color );
		private:
			CharBuffer* buffer;
			size_t curs_x, curs_y;
			unsigned int state;
			Color pri,sec;
		};

	} // namespace Term

#endif // TERMINATE_TTY_HPP
