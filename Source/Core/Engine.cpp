#include "Engine.h"
#include "Input.h"
#include "Menu.h"
#include "Texture.h"
#include "ChosenPhase.h"
#include "Pause.h"

Engine* Engine::s_Instance = nullptr;
State* Engine::m_CurrentState = nullptr;
void Engine::Init()
{
    if( SDL_Init( SDL_INIT_VIDEO ) != 0 && IMG_Init( IMG_INIT_JPG | IMG_INIT_PNG ) !=0)
    {
        SDL_Log( "Failed to initialize video: %s",SDL_GetError() );
    }

    if (TTF_Init() == -1) {
        SDL_Log("TTF_Init failed: %s\n", TTF_GetError());
    }
    //SDL_WindowFlags wf = ( SDL_WindowFlags ) ( SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI );
    m_Window = SDL_CreateWindow( "Loe Adventure", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0 ); //, wf );
    if( m_Window == nullptr )
    {
        SDL_Log( "Failed to create window: %s",SDL_GetError() );
    }

    m_Renderer = SDL_CreateRenderer( m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( m_Renderer == nullptr )
    {
        SDL_Log( "Failed to create renderer: %s",SDL_GetError() );
    }

    m_Font = TTF_OpenFont("assets/font/Pixel-UniCode.ttf", 64);
    if(m_Font == nullptr) {
        SDL_Log("Failed to create font: %s", TTF_GetError());
    }
    m_IsRunning = true;
    m_CurrentState = Menu::GetInstance();
    m_CurrentState->Init();
    ChosenPhase::GetInstance()->Init();
    Pause::GetInstance()->Init();
}

void Engine::Render()
{
    SDL_SetRenderDrawColor( m_Renderer, 0, 0, 0, 0);
    SDL_RenderClear(m_Renderer);

    m_CurrentState->Render();
    SDL_RenderPresent(m_Renderer);
}

void Engine::Update()
{
    m_CurrentState->Update();
}

void Engine::Quit()
{
    m_IsRunning = false;
}

void Engine::Event()
{
    Input::GetInstance()->Listen();
    m_CurrentState->Listen();
}

void Engine::Clean() {
    Texture::GetInstance()->Clean();
    SDL_DestroyRenderer( m_Renderer );
    SDL_DestroyWindow( m_Window );
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
}

void Engine::ChangeState(State* target) {
    m_CurrentState->Clean();
    m_CurrentState = target;
    m_CurrentState->Init();
}

void Engine::PushState(State *target) {
    m_CurrentState = target;
}
