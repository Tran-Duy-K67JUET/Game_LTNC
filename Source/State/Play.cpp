#include "Pause.h"
#include "Play.h"
#include "Input.h"
#include "Engine.h"
#include "Texture.h"
#include "Button.h"
#include "Timer.h"
#include "Menu.h"
#include "MapParser.h"
#include "Player.h"
#include "Camera.h"
#include "Enemy.h"


Play *Play::s_Instance = nullptr;
Button* pause = nullptr;
Player* player = nullptr;
Enemy* smile = nullptr;


void Play::Init()
{
    SDL_Log("Mode: Play");
    Texture::GetInstance()->Load("PlayBg", "assets/backgrounds/background_2.jpg");
    Texture::GetInstance()->Load("PlayBt", "assets/interface/pixelButton.png");
    Texture::GetInstance()->Load("Player", "assets/entities/player.png");
    Texture::GetInstance()->Load("Shoot", "assets/entities/spark-Sheet.png");
    Texture::GetInstance()->Load("Smile", "assets/entities/Smile.png");
    pause = new Button(new Properties("PlayBt", 0, 0, 192, 192), 5, 1, 0.25);
    if(!MapParser::GetInstance()->Load()) SDL_Log("Failed to load map!");
    m_LevelMap = MapParser::GetInstance()->GetMap("map0001");
    player = new Player(new Properties("Player", 100, 300, 100, 74));
    smile = new Enemy(new Properties("Smile", 200, 400, 32, 25), 8, 8, 5);
    Camera::GetInstance()->SetTarget( player->GetOrigin() );
}

void Play::Update()
{
    float dt = Timer::GetInstance()->GetDeltaTime();
    pause->Update(dt);
    m_LevelMap->Update();
    player->Update(dt);
    smile->Update(dt);
    Camera::GetInstance()->Update( dt );
}

void Play::Render()
{
    Texture::GetInstance()->Draw("PlayBg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    pause->Draw();
    m_LevelMap->Render();
    player->Draw();
    smile->Draw();
}

void Play::Clean()
{
    player->Clean();
    pause->Clean();
    Texture::GetInstance()->Drop("PlayBg");
    Texture::GetInstance()->Drop("Game");
}

void Play::Listen() {
    if(pause->IsPressed()) Engine::GetInstance()->ChangeState(Pause::GetInstance());
}

