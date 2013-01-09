#ifndef TERMINATE_TTY_HPP
#define TERMINATE_TTY_HPP

#include "charbuffer.hpp"
#include "string.hpp"

namespace Terminate
	{

	class TTY
		{
		public:
			enum : unsigned int { Wrap=1 };
			TTY( CharBuffer& );
			void PlaceCursor( size_t x, size_t y );
			void Put( Char );
			void Put( const String& );
		private:
			CharBuffer* buffer;
			size_t curs_x, curs_y;
			unsigned int state;
		};

	} // namespace Terminate

#endif // TERMINATE_TTY_HPP
