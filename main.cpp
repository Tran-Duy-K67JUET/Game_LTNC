#include <SDL2/SDL.h>
#include "Engine.h"
#include "Timer.h"
int main(int argc, char** argv) {
    SDL_Log("Good!");
    Engine::GetInstance()->Init();
    while(Engine::GetInstance()->IsRunning()) {
        Engine::GetInstance()->Event();
        Engine::GetInstance()->Update();
        Engine::GetInstance()->Render();
        Timer::GetInstance()->Tick();
    }
    Engine::GetInstance()->Clean();
    return 0;
}
