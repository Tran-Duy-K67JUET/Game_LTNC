#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <set>

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Vector2D.h"
#include "Attack.h"

#define JUMP_TIME 10.0f
#define JUMP_FORCE 20.0f
#define RUN_FORCE 15.0f
#define ATTACK_TIME 5.0f
#define PUNCH_TIME 7.5f
#define SHOOT_TIME 20.0f
#define COOL_DOWN 20.0f

class Player: public Character
{

    public:
        Player( Properties* props );

        virtual void Draw();
        virtual void Update( float dt );
        virtual void Clean();

        void GetHit();
        void DeadStatment();

        SDL_Rect GetBox() {return m_Collider->Get();}

        void SetSlash(int dmg) {Slash = dmg;}
        void SetShoot(int dmg) {Shoot = dmg;}

        int GetSlash() {return Slash;}
        int GetShoot() {return Shoot;}

        Attack* Hit() {return m_CurrentAttack;}
        void SetCurrentAttack(Attack* atk) {m_CurrentAttack = atk;}
        void UseItems(int Type, int inf);
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
        bool m_Hit;

        float m_PunchTime;
        float m_AttackTime;
        float m_JumpTime;
        float m_Jump_Force;
        float m_ShootTime;
        float m_CoolDown;

        int Slash;
        int Shoot;

        Collider* m_Collider;

        Animation* m_Animation;
        RigidBody* m_RigidBody;

        Vector2D m_LastSafePosition;

        static Attack *m_CurrentAttack;
};

#endif // PLAYER_H
