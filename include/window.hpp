#ifndef TERMINATE_WINDOW_HPP
#define TERMINATE_WINDOW_HPP

#include "charbuffer.hpp"
#include "context.hpp"


namespace Terminate
	{

	class Window
		{
		public:
			Window( Context&, TileCount width, TileCount height );
			void SetWindowSize( TileCount width, TileCount height );
			PixDim GetWindowPixWidth() const;
			PixDim GetWindowPixHeight() const;
			void Render( SDL_Surface* );

			void PutChar( size_t x, size_t y, Char c ) 
				{ buffer.PutChar(x,y,c); };
			Char GetChar( size_t x, size_t y ) const 
				{ return buffer.GetChar(x,y); }
			size_t Width() const { return buffer.Width(); }
			size_t Height() const { return buffer.Height(); }
		private:
			CharBuffer buffer;
			Context* context;
		};

	} // namespace Terminate

#endif //TERMINATE_WINDOW_HPP
