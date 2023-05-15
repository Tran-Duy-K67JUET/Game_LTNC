#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <vector>
#include "Enemy.h"
#include "Timer.h"
#include "Player.h"

class EnemyManager
{
    public:
        EnemyManager(Player* player);
        void Update(float dt);
        void Draw();
        void Clean();

        void CheckEnemy();
        void NewLevel(int Level);

    private:
        std::vector<Enemy*> m_Pooling;
        Player *m_player;

        int m_Size;
        int m_LevelCnt;
        int Defeated;

};

#endif // ENEMYMANAGER_H
