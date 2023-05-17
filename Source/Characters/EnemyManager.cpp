#include "EnemyManager.h"
#include "CollisionHandler.h"
#include "Enemy.h"
#include "Timer.h"
#include "ChosenPhase.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>

EnemyManager::EnemyManager(Player* player)
{
    m_LevelCnt = 0;
    m_Score = 0;
    m_Size = 1;
    m_player = player;
    NewLevel(m_LevelCnt);
}

void EnemyManager::NewLevel(int Level) {
    srand(time(NULL));
    m_Size += m_LevelCnt*2;
    int Health = m_LevelCnt*10+5;
    for(int i = m_Pooling.size(); i < m_Size; i++) {
        int r = rand()%900 + 10;
        m_Pooling.push_back(new Enemy(new Properties("Smile", r, 350, 32, 25), 8, 8, 5));
        m_Pooling[i]->SetPlayer(m_player);
    }

    for(auto e : m_Pooling) {
        e->SetHealth(Health);
    }
}

void EnemyManager::Update(float dt)
{

    // check enemy collsion
    for(auto e : m_Pooling) {
        CheckEnemy();
        if(e->StillAlive()) {
            e->Update(dt);
            if(m_player->Hit() != nullptr) {
                if(CollisionHandler::GetInstance()->CheckCollision(m_player->Hit()->GetBox(),e->GetBox())) {
                    m_player->Hit()->Moving(false);
                    e->GetHit(m_player->Hit()->GetDamage());
                    m_player->SetCurrentAttack(nullptr);
                }
            }
        }
    }
    //std::cout << Defeated << " " << m_Size << " " << m_LevelCnt << std::endl;

}

void EnemyManager::Draw()
{
    for(auto e : m_Pooling) if(e->StillAlive()) e->Draw();
}

void EnemyManager::Clean()
{
    for(auto e : m_Pooling) e->Clean();
}

void EnemyManager::CheckEnemy() {
    Defeated = 0;
    for(auto e : m_Pooling) {
        if(!e->StillAlive()) Defeated++;
    }
    m_Score += Defeated;
    if(Defeated == m_Size) {
        m_LevelCnt++;
        NewLevel(m_LevelCnt);
        ChosenPhase::GetInstance()->SetInfor(m_LevelCnt);
        ChosenPhase::GetInstance()->SetPlayer(m_player);
        Engine::GetInstance()->ChangeState(ChosenPhase::GetInstance());
    } else m_Score -= Defeated;
}
