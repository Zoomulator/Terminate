#include "window.hpp"
#include <stdexcept>
#include <iostream>


namespace Term
	{


	std::ostream&
	operator << ( std::ostream& os, const Color& col )
		{
		os << (int)col.r << " " << (int)col.g << " " << (int)col.b;
		return os;
		}


	Window::Window( Context& c, TileCount w, TileCount h ) :
		buffer(w,h),
		context(&c)
		{
		}


	void
	Window::SetWindowSize( TileCount width, TileCount height )
		{
		CharBuffer newBuffer(width,height);
		newBuffer.Copy(buffer,0,0);
		buffer = std::move(newBuffer);
		}


	void
	Window::Render( SDL_Surface* surf )
		{
		for( size_t y=0; y < buffer.Height(); ++y )
		for( size_t x=0; x < buffer.Width(); ++x )
			{
			Char ch = buffer.GetChar(x,y);
			SDL_Color colors[2] = { ch.GetPriColor(), ch.GetSecColor() };
			if( SDL_SetColors( context->GetTilemap(), colors, 0, 2 ) == 0 )
				throw std::runtime_error( "Tilemap missing palette." );

			Sint16 tilex = (ch.GetChar() % 16) *
				context->GetTileWidth();
			Sint16 tiley = (ch.GetChar() / 16) * 
					context->GetTileHeight();
			SDL_Rect tile = { 
				tilex, tiley,
				static_cast<Uint16>(context->GetTileWidth()),
				static_cast<Uint16>(context->GetTileHeight() )};
			SDL_Rect dst = {
				static_cast<Sint16>(x * context->GetTileWidth()),
				static_cast<Sint16>(y * context->GetTileHeight()),
				0,0 };
			SDL_BlitSurface( context->GetTilemap(), &tile, surf, &dst );
			}
		}


	PixDim
	Window::GetWindowPixWidth() const
		{
		return Width() * context->GetTileWidth();
		}


	PixDim
	Window::GetWindowPixHeight() const
		{
		return Height() * context->GetTileHeight();
		}
	}// namespace Term
