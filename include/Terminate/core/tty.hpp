/////////////////////////////////////////////
// Copyright (c) 2013 Kim Simmons
// Distributed under the Zlib/libPNG license.
// Read LICENSE.txt accompanying this source 
// for more information.
/////////////////////////////////////////////

#ifndef TERMINATE_TTY_HPP
#define TERMINATE_TTY_HPP

#include "buffer.hpp"
#include "string.hpp"

namespace Term
	{
	typedef unsigned StateBit;
	class TTY
		{
		public:
			enum : StateBit // State bitflags
				{
				Wrap   = 1,
				Insert = 2,
				VScroll = 4
				};
			TTY( Buffer& );
			TTY& Set( StateBit b, bool setTo=true );
			bool IsSet( StateBit b ) const;
			Char Peek() const;
			TTY& Place( size_t x, size_t y );
			TTY& ClearLine();
			TTY& Put( Char );
			TTY& Put( const String& );
			TTY& Put( char );
			TTY& Put( const std::string& );
			TTY& PriColor( Color );
			TTY& SecColor( Color );
		private:
			Buffer* buffer;
			int curs_x, curs_y;
			StateBit state;
			Color pri,sec;
		};

	} // namespace Term

#endif // TERMINATE_TTY_HPP
