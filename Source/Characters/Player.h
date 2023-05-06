#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Vector2D.h"
#include "Attack.h"

#define JUMP_TIME 10.0f
#define JUMP_FORCE 20.0f
#define RUN_FORCE 15.0f
#define ATTACK_TIME 20.0f
#define PUNCH_TIME 7.5f
#define SHOOT_TIME 20.0f

class Player: public Character
{

    public:
        Player( Properties* props );

        virtual void Draw();
        virtual void Update( float dt );
        virtual void Clean();

    private:
        void AnimationState();

    private:
        bool m_IsJumping;
        bool m_IsGrounded;
        bool m_IsAttacking;
        bool m_IsRunning;
        bool m_IsFalling;
        bool m_IsPunching;
        bool m_IsShoot;
        bool m_IsLeft;

        float m_PunchTime;
        float m_AttackTime;
        float m_JumpTime;
        float m_Jump_Force;
        float m_ShootTime;

        Collider* m_Collider;

        Animation* m_Animation;
        RigidBody* m_RigidBody;

        Vector2D m_LastSafePosition;
};

#endif // PLAYER_H
