#ifndef TILELAYER_H
#define TILELAYER_H

#include <string>
#include <vector>
#include "Layer.h"

//debug
#include "Collider.h"
#include "SDL2/SDL.h"
#include "Camera.h"
#include "Vector2D.h"

struct Tileset
{
    int FirstID, LastID;
    int RowCount, ColCount;
    int TileCount, TileSize;
    std::string Name, Source;
};

using TilesetList = std::vector<Tileset>;
// the space at the end seems important
using TileMap = std::vector<std::vector<int> >;

class TileLayer : public Layer
{
    public:
        TileLayer( int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesets );
        virtual void Render();
        virtual void Update();
        inline TileMap GetTilemap(){ return m_Tilemap; }

        int GetTileSize() {return m_Tilesize;}
        int GetWidth() {return m_Tilesize * m_ColCount;}
        int GetHeight() {return m_Tilesize * m_RowCount;}

    private:
        int m_Tilesize;
        int m_RowCount, m_ColCount;
        TileMap m_Tilemap;
        TilesetList m_Tilesets;
};

#endif // TILELAYER_H
