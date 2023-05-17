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
#include "EnemyManager.h"
#include "Sound.h"
#include "ChosenPhase.h"


Play *Play::s_Instance = nullptr;
Button* pause = nullptr;
Button* infor = nullptr;
Player* player = nullptr;
EnemyManager *smile = nullptr;



void Play::Init()
{
    SDL_Log("Mode: Play");
    Texture::GetInstance()->Load("PlayBg", "assets/backgrounds/background_2.jpg");
    Texture::GetInstance()->Load("PlayBt", "assets/interface/pixelButton.png");
    Texture::GetInstance()->Load("Player", "assets/entities/player.png");
    Texture::GetInstance()->Load("Shoot", "assets/entities/spark-Sheet.png");
    Texture::GetInstance()->Load("Slash", "assets/entities/slash.png");
    Texture::GetInstance()->Load("Smile", "assets/entities/Smile.png");
    Texture::GetInstance()->Load("Infor", "assets/interface/infor.png");

    Sound::GetInstance()->LoadMusic("PlaySound", "assets/sounds/Play.wav");
    Sound::GetInstance()->LoadEffect("Shoot", "assets/sounds/Shoot.wav");
    Sound::GetInstance()->LoadEffect("Slash", "assets/sounds/Slash.wav");

    pause = new Button(new Properties("PlayBt", 0, 0, 192, 192), 5, 1, 0.25);
    infor = new Button(new Properties("Infor", 0, 570, 500, 100), 0, 0, 0.75);

    if(!MapParser::GetInstance()->Load()) SDL_Log("Failed to load map!");
    m_LevelMap = MapParser::GetInstance()->GetMap("map0001");
    player = new Player(new Properties("Player", 100, 300, 100, 74));
    smile = new EnemyManager(player);
    Camera::GetInstance()->SetTarget( player->GetOrigin() );
    Sound::GetInstance()->PlayMusic("PlaySound");
    ChosenPhase::GetInstance()->SetPlayer(player);
}

void Play::Update()
{
    float dt = Timer::GetInstance()->GetDeltaTime();
    pause->Update(dt);
    infor->Update(dt);
    m_LevelMap->Update();
    player->Update(dt);
    smile->Update(dt);

    Pause::GetInstance()->GetScore(smile->GetLever(), smile->GetScore());
    Camera::GetInstance()->Update( dt );
}

void Play::Render()
{
    Texture::GetInstance()->Draw("PlayBg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    pause->Draw();
    m_LevelMap->Render();
    player->Draw();
    smile->Draw();
    infor->Draw();

    Texture::GetInstance()->DrawText("Round", "Round " + std::to_string(smile->GetLever()), 400, 0, 1);
    Texture::GetInstance()->DrawText("Health", std::to_string(player->GetHealth()), 45, 578, 0.5);
    Texture::GetInstance()->DrawText("Health", std::to_string(player->GetSlash()), 95, 578, 0.5);
    Texture::GetInstance()->DrawText("Health", std::to_string(player->GetShoot()), 145, 578, 0.5);
}

void Play::Clean()
{
    //player->Clean();
    //pause->Clean();
    //Sound::GetInstance()->Clean();
    Texture::GetInstance()->Drop("PlayBg");
    Texture::GetInstance()->Drop("Game");
}

void Play::Listen() {
    if(pause->IsPressed()) Engine::GetInstance()->ChangeState(Pause::GetInstance());
}

