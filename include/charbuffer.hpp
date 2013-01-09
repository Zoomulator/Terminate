#ifndef TERMINATE_CHARBUFFER_HPP
#define TERMINATE_CHARBUFFER_HPP

#include <cstdlib>
#include <memory>
#include "char.hpp"


namespace Terminate
	{

	
	class CharBuffer
		{
		public:
			CharBuffer( size_t width, size_t height );
			size_t Width() const;
			size_t Height() const;
			void PutChar( size_t x, size_t y, Char );
			Char GetChar( size_t x, size_t y ) const;
			void Copy( const CharBuffer&, int ox, int oy );

		private:
			size_t width, height;
			std::unique_ptr<Char[]> buffer;
		};


	} // namespace Terminate

#endif //TERMINATE_CHARBUFFER_HPP
