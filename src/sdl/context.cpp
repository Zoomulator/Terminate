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
    Context::RenderTarget( SDL_Surface* surf )
        {
        drawSurf = surf;
        }


    void
    Context::Tilemap( std::string path )
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
    Context::Tilemap()
        {
        return tilemap;
        }


    PixDim
    Context::TileWidth() const
        {
        return twidth;
        }


    PixDim
    Context::TileHeight() const
        {
        return theight;
        }


    void
    Context::Print( Char ch, size_t x, size_t y ) const
        {
        SDL_Color colors[2] = {
            toSDLColor( ch.PriColor() ),
            toSDLColor( ch.SecColor() ) };
        if( SDL_SetColors( tilemap, colors, 0, 2 ) == 0 )
            throw std::runtime_error(
                "Tilemap missing palette." );

        // Convert the ASCII value to tilemap coordinates.
        Sint16 tilex = (ch.ASCII() % 16) * TileWidth();
        Sint16 tiley = (ch.ASCII() / 16) * TileHeight();
        SDL_Rect tile = {
            tilex, tiley,
            static_cast<Uint16>(TileWidth()),
            static_cast<Uint16>(TileHeight())};
        SDL_Rect dst = {
            static_cast<Sint16>(x * TileWidth()),
            static_cast<Sint16>(y * TileHeight()),
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
