#include "Pause.h"
#include "Play.h"
#include "Input.h"
#include "Engine.h"
#include "Texture.h"
#include "Button.h"
#include "Timer.h"
#include "Menu.h"
Pause* Pause::s_Instance = nullptr;
Button *resume = nullptr;
Button *menu = nullptr;
Button *repeat = nullptr;
void Pause::Init()
{
    SDL_Log("Pause mode!");
    Texture::GetInstance()->Load("PlayBg", "assets/backgrounds/background_2.jpg");
    Texture::GetInstance()->Load("PlayBt", "assets/interface/pixelButton.png");
    resume = new Button(new Properties("PlayBt", 375, 375, 192, 192), 6, 0, 1);
    menu = new Button(new Properties("PlayBt", 175, 375, 192, 192), 0, 1, 1);
    repeat = new Button(new Properties("PlayBt", 575, 375, 192, 192), 6, 1, 1);
}

void Pause::Update()
{
    float dt = Timer::GetInstance()->GetDeltaTime();
    resume->Update(dt);
    menu->Update(dt);
    repeat->Update(dt);
}

void Pause::Render()
{
    Texture::GetInstance()->Draw("PlayBg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    resume->Draw();
    menu->Draw();
    repeat->Draw();
}

void Pause::Clean()
{
    resume->Clean();
    menu->Clean();
    repeat->Clean();
    Texture::GetInstance()->Drop("PlayBg");
}

void Pause::Listen()
{
    if(resume->IsPressed()) Engine::GetInstance()->PushState(Play::GetInstance());
    if(menu->IsPressed()) Engine::GetInstance()->ChangeState(Menu::GetInstance());
    if(repeat->IsPressed()) Engine::GetInstance()->ChangeState(Play::GetInstance());
}
