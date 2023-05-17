#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Animation.h"
#include "Vector2d.h"
#include "Player.h"

#define MOVE_TIME 50.0f
#define IDLE_TIME 50.0f
#define RUN_FORCE 15.0f
#define SMILE_ATTACK_TIME 20.0f
#define DEAD_TIME 5.0f

class Enemy: public Character
{

    public:
        Enemy(Properties* props, int AttackFrame, int IdleFrame, int DeadFrame);
        virtual void Draw();
        virtual void Update( float dt );
        virtual void Clean();

        void SetPlayer(Player* plr) {
            m_Player = plr;
        }

        SDL_Rect GetBox() {
            return m_Collider->Get();
        }

        bool StillAlive();

        void GetHit(int DmgTaken) {
            Health -= DmgTaken;
            std::cout << Health << std::endl;
        }

        void SetHealth(int h) {
            Health = h;
            m_IsDead = false;
        }
    private:
        void AnimationState();
    private:
        bool m_IsGrounded;
        bool m_IsAttacking;
        bool m_IsRunning;
        bool m_IsLeft;
        bool m_Dying;
        bool m_IsDead;

        float m_AttackTime;
        float m_RunTime;
        float m_IdleTime;
        float m_DeadTime;

        int m_AttackFrame;
        int m_IdleFrame;
        int m_DeadFrame;

        Collider* m_Collider;

        Animation* m_Animation;
        RigidBody* m_RigidBody;

        Vector2D m_LastSafePosition;

        Player* m_Player;
        Attack* m_Attack;
};

#endif // ENEMY_H
