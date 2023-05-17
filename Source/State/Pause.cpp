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
    m_Death = false;
    Texture::GetInstance()->Load("PlayBg", "assets/backgrounds/background_2.jpg");
    Texture::GetInstance()->Load("PlayBt", "assets/interface/pixelButton.png");
    resume = new Button(new Properties("PlayBt", 375, 375, 192, 192), 6, 0, 1);
    menu = new Button(new Properties("PlayBt", 175, 375, 192, 192), 0, 1, 1);
    repeat = new Button(new Properties("PlayBt", 575, 375, 192, 192), 6, 1, 1);
}

void Pause::Update()
{
    float dt = Timer::GetInstance()->GetDeltaTime();
    if(!m_Death) resume->Update(dt);
    menu->Update(dt);
    repeat->Update(dt);
}

void Pause::Render()
{
    Texture::GetInstance()->Draw("PlayBg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    if(!m_Death) resume->Draw();
    if (m_Death) Texture::GetInstance()->DrawText("HighScre", "High score:   "+std::to_string(r)+"   levels   "+ std::to_string(s)+ "  scores ", 300, 200, 0.5);
    menu->Draw();
    repeat->Draw();
}

void Pause::Clean()
{
    //resume->Clean();
    //menu->Clean();
    //repeat->Clean();
    Texture::GetInstance()->Drop("PlayBg");
}

void Pause::Listen()
{
    if(!m_Death) if(resume->IsPressed()) Engine::GetInstance()->PushState(Play::GetInstance());
    if(menu->IsPressed()) Engine::GetInstance()->ChangeState(Menu::GetInstance());
    if(repeat->IsPressed()) Engine::GetInstance()->ChangeState(Play::GetInstance());
}

