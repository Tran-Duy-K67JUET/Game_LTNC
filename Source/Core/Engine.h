#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_ttf.h>
#include "State.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

class Engine
{
    public:
        static Engine* GetInstance() { return s_Instance = ( s_Instance != nullptr ) ? s_Instance : new Engine(); }
        void Init();

        void Render();
        void Update();
        void Quit();
        void Clean();
        void Event();

        void ChangeState(State *target);
        void PushState(State *target);
        SDL_Renderer* GetRenderer() {return m_Renderer;}
        TTF_Font* GetFont() {return m_Font;}
        inline bool IsRunning() {return m_IsRunning;}
    private:
        Engine() {}
        bool m_IsRunning;
        static Engine* s_Instance;
        static State* m_CurrentState;
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        TTF_Font* m_Font;
};

#endif // ENGINE_H
