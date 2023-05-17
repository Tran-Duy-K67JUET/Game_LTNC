#include "ChosenPhase.h"
#include "Texture.h"
#include "Button.h"
#include "Timer.h"
#include "Engine.h"
#include "Play.h"

ChosenPhase* ChosenPhase::s_Instance = nullptr;
Button* apple = nullptr;
Button* medicine = nullptr;
Button* gold = nullptr;

void ChosenPhase::Init()
{
    SDL_Log("Chosing mode!");
    m_Infor = 0;
    Texture::GetInstance()->Load("PlayBg", "assets/backgrounds/background_2.jpg");
    Texture::GetInstance()->Load("Items", "assets/interface/items.png");
    apple = new Button(new Properties("Items", 425, 375, 100, 100), 0, 0, 1.5);
    medicine = new Button(new Properties("Items", 225, 375, 100, 100), 0, 1, 1.5);
    gold = new Button(new Properties("Items", 625, 375, 100, 100), 0, 2, 1.5);
}

void ChosenPhase::Update()
{
    float dt = Timer::GetInstance()->GetDeltaTime();
    apple->Update(dt);
    medicine->Update(dt);
    gold->Update(dt);
}

void ChosenPhase::Render()
{
    Texture::GetInstance()->Draw("PlayBg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    Texture::GetInstance()->DrawText("ChosePhase", "CHOOSE AN ITEM!", 350, 150, 1);
    apple->Draw();
    if(apple->IsHover()) Texture::GetInstance()->DrawText("ItemInfor", "Recover " + std::to_string((m_Infor + 1)*2) + "  lifes", 400, 300, 0.5);
    medicine->Draw();
    if(medicine->IsHover()) Texture::GetInstance()->DrawText("ItemInfor", "Gain " + std::to_string((m_Infor + 1)*5) + "  magic damage", 400, 300, 0.5);
    gold->Draw( );
    if(gold->IsHover()) Texture::GetInstance()->DrawText("ItemInfor", "Gain " + std::to_string((m_Infor + 1)*2)+ "  attack damage", 400, 300, 0.5);
}

void ChosenPhase::Clean()
{
    apple->Clean();
    medicine->Clean();
    gold->Clean();
    Texture::GetInstance()->Drop("PlayBg");
}

void ChosenPhase::Listen()
{
    if(apple->IsPressed()) {
        m_player->UseItems(1, (m_Infor+1)*2);
        Engine::GetInstance()->PushState(Play::GetInstance());
    }
    if(medicine->IsPressed()) {
        m_player->UseItems(3, ((m_Infor + 1)*5));
        Engine::GetInstance()->PushState(Play::GetInstance());
    }
    if(gold->IsPressed()) {
        m_player->UseItems(2,(m_Infor + 1)*2);
        Engine::GetInstance()->PushState(Play::GetInstance());
    }
}
