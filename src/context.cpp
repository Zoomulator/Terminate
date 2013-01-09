#include "context.hpp"
#include <SDL/SDL_image.h>
#include <stdexcept>


namespace Term
	{

	

	Context::Context() :
		twidth(0), theight(0),
		tilemap(nullptr)
		{
		}


	Context::~Context()
		{
		if( tilemap != nullptr )
			SDL_FreeSurface(tilemap);
		}


	void
	Context::SetTilemap( std::string path )
		{
		if( tilemap != nullptr )
			SDL_FreeSurface(tilemap);

		tilemap = IMG_Load( path.c_str() );
		if( tilemap == nullptr )
			throw std::runtime_error( "Error opening file: " + path );
		if( tilemap->format->BitsPerPixel != 8 )
			throw std::runtime_error( "PNG file must be color indexed" );

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


	} // namespace Term
