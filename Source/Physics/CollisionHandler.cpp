#include "CollisionHandler.h"
#include "Play.h"
#include "Engine.h"
#include "MapParser.h"
#include <iostream>

CollisionHandler* CollisionHandler::s_Instance = nullptr; // init singleton

CollisionHandler::CollisionHandler()
{
    m_CollisionLayer = ( TileLayer* )Play::GetInstance()->GetMap()->GetMapLayers().front();
    m_CollisionTilemap = m_CollisionLayer->GetTilemap();
}

bool CollisionHandler::CheckCollision(SDL_Rect a, SDL_Rect b)
{
    //AABB algorithm
    bool x_overlaps = (( a.x < b.x + b.w ) && ( a.x + a.w > b.x ));
    bool y_overlaps = (( a.y < b.y + b.h ) && ( a.y + a.h > b.y ));
    return ( x_overlaps && y_overlaps );
}

bool CollisionHandler::MapCollision(SDL_Rect a)
{
    int tileSize = 16;
    int rowCount = 40;
    int colCount = 80;


    int left_tile = a.x/tileSize;
    int right_tile = ( a.x + a.w )/tileSize;

    int top_tile = a.y/tileSize;
    int bottom_tile = ( a.y + a.h )/tileSize;

    if ( left_tile < 0 ) left_tile = 0;
    if ( right_tile > colCount ) right_tile = colCount;

    if ( top_tile < 0 ) top_tile = 0;
    if ( bottom_tile > rowCount ) bottom_tile = rowCount;

    for ( int i = left_tile; i <= right_tile; ++i )
    {
        for ( int j = top_tile; j <= bottom_tile; ++j )
        {
            if ( m_CollisionTilemap [j][i] > 0 )
            {
                return true;
            }
        }
    }
    return false;
}


int CollisionHandler::MapEndX(SDL_Rect Position) {
    Size Map = MapParser::GetInstance()->GetMapSize("map0001");
    if(Position.x + Position.w >= Map.colcount * Map.tilesize) {
        return Map.colcount * Map.tilesize - Position.w;
    }
    if(Position.x < 0) return 0;
    return -1;
}

int CollisionHandler::MapEndY(SDL_Rect Position) {
    Size Map = MapParser::GetInstance()->GetMapSize("map0001");
    if(Position.y + Position.h >= Map.rowcount * Map.tilesize) {
        return Map.rowcount * Map.tilesize - Position.y;
    }
    return -1;
}
