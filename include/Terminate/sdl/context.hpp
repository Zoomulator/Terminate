/////////////////////////////////////////////
// Copyright (c) 2013 Kim Simmons
// Distributed under the Zlib/libPNG license.
// Read LICENSE.txt accompanying this source 
// for more information.
/////////////////////////////////////////////

#ifndef TERMINATE_SDLCONTEXT_HPP
#define TERMINATE_SDLCONTEXT_HPP

#include "../terminate.hpp"
#include <SDL/SDL.h>


namespace Term
	{
namespace SDL
	{

	inline
	SDL_Color toSDLColor( const Color& c )
		{
		SDL_Color sdl;
		sdl.r = c.r;
		sdl.g = c.g;
		sdl.b = c.b;
		return sdl;
	}


	class Context : public Term::Context
		{
		public:
			Context( size_t width, size_t height );
			~Context();
			void SetRenderTarget( SDL_Surface* );

			void SetTilemap( std::string path );
			SDL_Surface* GetTilemap();
			PixDim GetTileWidth() const;
			PixDim GetTileHeight() const;
			virtual void Print( Char ch, size_t x, size_t y ) const override;
			virtual void Print() const override;

		private:
			PixDim twidth,theight;
			SDL_Surface* tilemap;
			SDL_Surface* drawSurf;
		};


	} // namespace SDL
	} // namespace Term
#endif //TERMINATE_SDLCONTEXT_HPP
