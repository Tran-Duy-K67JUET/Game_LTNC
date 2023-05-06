#ifndef INPUT_H
#define INPUT_H

#include "SDL2/SDL.h"
#include "Vector2d.h"

class Input
{
    public:
        static Input* GetInstance() { return s_Instance = ( s_Instance != nullptr ) ? s_Instance : new Input(); }
        bool GetMouseDown();
        Vector2D GetMousePosition();
        bool GetKeyDown(SDL_Scancode key);
        void Listen();

    private:
        Input();
        void KeyUp();
        void KeyDown();

        const Uint8* m_KeyStates;
        static Input* s_Instance;

};

#endif // INPUT_H
