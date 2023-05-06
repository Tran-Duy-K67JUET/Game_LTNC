#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Animation.h"
#include "Vector2d.h"

#define MOVE_TIME 50.0f
#define IDLE_TIME 50.0f
#define RUN_FORCE 15.0f
#define ATTACK_TIME 20.0f
#define PUNCH_TIME 7.5f

class Enemy: public Character
{

    public:
        Enemy(Properties* props, int AttackFrame, int IdleFrame, int DeadFrame);

        virtual void Draw();
        virtual void Update( float dt );
        virtual void Clean();

    private:
        void AnimationState();

    private:
        bool m_IsGrounded;
        bool m_IsAttacking;
        bool m_IsRunning;
        bool m_IsLeft;

        float m_AttackTime;
        float m_RunTime;
        float m_IdleTime;

        int m_AttackFrame;
        int m_IdleFrame;
        int m_DeadFrame;

        Collider* m_Collider;

        Animation* m_Animation;
        RigidBody* m_RigidBody;

        Vector2D m_LastSafePosition;
};

#endif // ENEMY_H
