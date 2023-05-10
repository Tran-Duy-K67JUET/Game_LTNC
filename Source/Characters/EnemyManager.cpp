#include "EnemyManager.h"
#include "CollisionHandler.h"
#include "Enemy.h"
#include "Timer.h"
#include <iostream>
#include <cstdlib>
#include <time.h>

EnemyManager::EnemyManager(Player* player)
{
    m_Size = 1;
    srand(time(NULL));
    m_player = player;
    // add more enemy through level
    for(int i = m_Pooling.size(); i < m_Size; i++) {
        int r = rand()%1280;
        m_Pooling.push_back(new Enemy(new Properties("Smile", r, 400, 32, 25), 8, 8, 5));
        m_Pooling[i]->SetPlayer(player);
    }
}
void EnemyManager::Update(float dt)
{
    for(auto e : m_Pooling) {
        e->Update(dt);
        Attack* a = m_player->Hit();
        if(a != nullptr) {
            std::cout << a->GetBox().x + a->GetBox().w << " " << e->GetBox().x << std::endl;
            if(CollisionHandler::GetInstance()->CheckCollision(e->GetBox(), a->GetBox())) {
                e->GetHit(a->GetDamage());
                m_player->HitTarget(true);
            }
            m_player->SetCurrentAttack(nullptr);
        } else {
            m_player->HitTarget(false);
        }
    }

}

void EnemyManager::Draw()
{
    for(auto e : m_Pooling) e->Draw();
}

void EnemyManager::Clean()
{
    for(auto e : m_Pooling) e->Clean();
}
