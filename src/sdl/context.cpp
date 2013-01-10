/////////////////////////////////////////////
// Copyright (c) 2013 Kim Simmons
// Distributed under the Zlib/libPNG license.
// Read LICENSE.txt accompanying this source 
// for more information.
/////////////////////////////////////////////

#include "sdl/context.hpp"
#include <iostream>
#include <SDL/SDL_image.h>
#include <stdexcept>


namespace Term
	{
namespace SDL
	{
	

	Context::Context( size_t width, size_t height) :
		Term::Context(width,height),
		twidth(0), theight(0),
		tilemap(nullptr),
		drawSurf(nullptr)
		{
		}


	Context::~Context()
		{
		if( tilemap != nullptr )
			SDL_FreeSurface(tilemap);
		}


	void
	Context::SetRenderTarget( SDL_Surface* surf )
		{
		drawSurf = surf;
		}


	void
	Context::SetTilemap( std::string path )
		{
		SDL_Surface* newTilemap = IMG_Load( path.c_str() );
		if( newTilemap == nullptr )
			throw std::runtime_error( "Error opening file: " + path );
		if( newTilemap->format->BitsPerPixel != 8 )
			throw std::runtime_error( "Image must be color indexed: "+path );

		if( tilemap != nullptr )
			SDL_FreeSurface(tilemap);
		tilemap = newTilemap;
		twidth = tilemap->w / 16;
		theight = tilemap->h / 16;
		}


	SDL_Surface*
	Context::GetTilemap()
		{
		return tilemap;
		}


	PixDim
	Context::GetTileWidth() const
		{
		return twidth;
		}


	PixDim
	Context::GetTileHeight() const
		{
		return theight;
		}


	void
	Context::Print( Char ch, size_t x, size_t y ) const
		{
		SDL_Color colors[2] = {
			toSDLColor( ch.GetPriColor() ),
			toSDLColor( ch.GetSecColor() ) };
		if( SDL_SetColors( tilemap, colors, 0, 2 ) == 0 )
			throw std::runtime_error(
				"Tilemap missing palette." );

		Sint16 tilex = (ch.GetChar() % 16) * GetTileWidth();
		Sint16 tiley = (ch.GetChar() / 16) * GetTileHeight();
		SDL_Rect tile = { 
			tilex, tiley,
			static_cast<Uint16>(GetTileWidth()),
			static_cast<Uint16>(GetTileHeight() )};
		SDL_Rect dst = {
			static_cast<Sint16>(x * GetTileWidth()),
			static_cast<Sint16>(y * GetTileHeight()),
			0,0 };
		SDL_BlitSurface( tilemap, &tile, drawSurf, &dst );
		}


	void
	Context::Print() const
		{
		for( size_t y=0; y<buffer.Height(); ++y )
		for( size_t x=0; x<buffer.Width(); ++x )
			Print( buffer.Get(x,y), x, y );
		}


	} // namespace SDL
	} // namespace Term
