/////////////////////////////////////////////
// Copyright (c) 2013 Kim Simmons
// Distributed under the Zlib/libPNG license.
// Read LICENSE.txt accompanying this source 
// for more information.
/////////////////////////////////////////////

#ifndef TERMINATE_TTY_HPP
#define TERMINATE_TTY_HPP

#include "charbuffer.hpp"
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
			TTY( CharBuffer& );
			void Set( StateBit b, bool setTo=true );
			bool IsSet( StateBit b ) const;
			void PlaceCursor( size_t x, size_t y );
			void ClearLine();
			Char Get() const;
			void Put( Char );
			void Put( const String& );
			void Put( char );
			void Put( const std::string& );
			void SetPriColor( Color );
			void SetSecColor( Color );
		private:
			CharBuffer* buffer;
			int curs_x, curs_y;
			StateBit state;
			Color pri,sec;
		};

	} // namespace Term

#endif // TERMINATE_TTY_HPP
