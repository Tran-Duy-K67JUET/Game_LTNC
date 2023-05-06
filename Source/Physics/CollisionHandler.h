#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include <vector>
#include "SDL2/SDL.h"
#include "TileLayer.h"
#include "GameMap.h"

class CollisionHandler
{
    public:
        bool MapCollision( SDL_Rect a );
        bool CheckCollision( SDL_Rect a, SDL_Rect b );
        int MapEndX(SDL_Rect position);
        int MapEndY(SDL_Rect Position);
        inline static CollisionHandler* GetInstance(){ return s_Instance = (s_Instance != nullptr)? s_Instance : new CollisionHandler(); }


    private:
        CollisionHandler();
        TileMap m_CollisionTilemap;
        TileLayer* m_CollisionLayer;
        static CollisionHandler* s_Instance;
};

#endif // COLLISIONHANDLER_H
