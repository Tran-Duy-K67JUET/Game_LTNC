#ifndef COLLIDER_H
#define COLLIDER_H

#include "SDL2/SDL.h"
#include "Engine.h"
#include "Camera.h"
#include "Vector2D.h"


class Collider
{
    public:
        inline SDL_Rect Get(){ return m_Box; }
        inline void SetBuffer( int x, int y, int w, int h ) { m_Buffer = { x, y, w, h }; }
        void DrawDebug()
        {
            Vector2D cam = Camera::GetInstance()->GetPosition();
            m_Box.x -= cam.X;
            m_Box.y -= cam.Y;
            SDL_RenderDrawRect( Engine::GetInstance()->GetRenderer(), &m_Box);
        }

        void Set( int x, int y, int w, int h )
        {
            m_Box = {
                x - m_Buffer.x,
                y - m_Buffer.y,
                w - m_Buffer.w,
                h - m_Buffer.h,
            };
        }
        void Clean() {
            m_Box = {0, 0, 0, 0};
            m_Buffer = {0, 0, 0, 0};
        }
    private:
    SDL_Rect m_Box;
    SDL_Rect m_Buffer;
};

#endif // COLLIDER_H
