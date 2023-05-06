#include "Menu.h"
#include "Input.h"
#include "Play.h"
#include "Engine.h"
#include "Texture.h"
#include "Button.h"
#include "Timer.h"

Menu *Menu::s_Instance = nullptr;
Button *play = nullptr;
Button *quit = nullptr;
Button *ranking = nullptr;
void Menu::Init()
{
    SDL_Log("Mode: Menu");
    Texture::GetInstance()->Load("MenuBg", "assets/backgrounds/Background.png");
    Texture::GetInstance()->Load("PlayBt", "assets/interface/pixelButton.png");
    play = new Button(new Properties("PlayBt", 320, 480, 192, 192), 6, 0, 0.5);
    quit = new Button(new Properties("PlayBt", 520, 480, 192, 192), 1, 0, 0.5);
    ranking = new Button (new Properties("PlayBt", 420, 480, 192, 192), 0, 0, 0.5);
}

void Menu::Update()
{
    float dt = Timer::GetInstance()->GetDeltaTime();
    play->Update(dt);
    quit->Update(dt);
    ranking->Update(dt);
}

void Menu::Render()
{
    Texture::GetInstance()->Draw("MenuBg", 0, -125, SCREEN_WIDTH, 768);
    Texture::GetInstance()->DrawText("Game", "Joe Adventrue!", 320, 160, 1);
    play->Draw();
    quit->Draw();
    ranking->Draw();
    if(play->IsHover()) Texture::GetInstance()->DrawText("PlayTx", "Play Game!", 420, 440, 0.5);
    else Texture::GetInstance()->Drop("PlayTx");
    if(ranking->IsHover()) Texture::GetInstance()->DrawText("RkTx", "See Ranking!", 420, 440, 0.5);
    else Texture::GetInstance()->Drop("RkTx");
    if(quit->IsHover()) Texture::GetInstance()->DrawText("QTx", "Quit Game!", 420, 440, 0.5);
    else Texture::GetInstance()->Drop("QTx");
}

void Menu::Clean()
{
    play->Clean();
    quit->Clean();
    ranking->Clean();
    Texture::GetInstance()->Drop("MenuBg");
    Texture::GetInstance()->Drop("Game");
}

void Menu::Listen() {
    if(play->IsPressed()) Engine::GetInstance()->ChangeState(Play::GetInstance());
    if(quit->IsPressed()) Engine::GetInstance()->Quit();
}
