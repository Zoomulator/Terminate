#ifndef TERMINATE_CONTEXT_HPP
#define TERMINATE_CONTEXT_HPP

#include <SDL/SDL.h>
#include <string>

namespace Term
	{
	typedef int TileCount;
	typedef int TileSize;
	typedef int PixDim;
	class Context
		{
		public:
			Context();
			~Context();

			void SetTilemap( std::string path );
			SDL_Surface* GetTilemap();
			PixDim GetTileWidth() const;
			PixDim GetTileHeight() const;
		private:
			PixDim twidth,theight;
			SDL_Surface* tilemap;
		};

	} // namespace Term

#endif //TERMINATE_CONTEXT_HPP
