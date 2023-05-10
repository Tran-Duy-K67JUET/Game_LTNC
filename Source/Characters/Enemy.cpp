#include <SDL.h>
#include <math.h>
#include "Enemy.h"
#include "Texture.h"
#include "Input.h"
#include "Camera.h"
#include "CollisionHandler.h"
#include <iostream>

Enemy::Enemy(Properties* props, int AttackFrame, int IdleFrame, int DeadFrame): Character(props)
{
    SDL_Log("Enemy Init!");
    m_AttackFrame = AttackFrame;
    m_IdleFrame = IdleFrame;
    m_DeadFrame = DeadFrame;


    m_IsAttacking = false;
    m_IsRunning = false;
    m_IsGrounded = false;
    m_IsLeft = false;
    m_IsDead = false;

    m_Flip = SDL_FLIP_NONE;
    m_AttackTime = ATTACK_TIME;
    m_RunTime = MOVE_TIME;
    m_IdleTime = IDLE_TIME;

    m_Collider = new Collider();
    m_Collider->SetBuffer( 0, 0, 0, 0);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity( 9.8f );

    m_Animation = new Animation();
    m_Attack = new Attack(new Properties("attack", 200, 200, 32, 25), (0, 0));

    Health = 100;
}

void Enemy::Draw()
{
    m_Animation->Draw( m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Flip );
    m_Collider->DrawDebug();
    if(m_IsAttacking) m_Attack->Draw();
}

void Enemy::Update(float dt)
{
    m_IsRunning = false;
    m_RigidBody->UnSetForce();

    //auto move to player
    if(m_IsDead == false) {
        if(GetTrans()->X > m_Player->GetTrans()->X + 60) {
            m_Flip = SDL_FLIP_NONE;
            m_IsRunning = true; m_RigidBody->ApplyForceX(BACKWARD*RUN_FORCE*0.25);
            m_IsLeft = true;
        } else if(GetTrans()->X < m_Player->GetTrans()->X) {
            m_Flip = SDL_FLIP_HORIZONTAL;
            m_IsRunning = true; m_RigidBody->ApplyForceX(FORWARD*RUN_FORCE*0.25);
            m_IsLeft = false;
        } else {
            m_IsAttacking = true;
            m_IsRunning = false;
        }
    }

    if(m_IsAttacking && m_AttackTime > 0) {
        m_AttackTime -= dt;
        m_Attack->Update(dt);
        if(CollisionHandler::GetInstance()->CheckCollision(m_Attack->GetBox(), m_Player->GetBox()) && (m_AttackTime < 10.0f)) {
            m_Player->GetHit(true);
        }
    } else {
        m_IsAttacking = false;
        m_AttackTime = ATTACK_TIME;
        m_Attack->SetPosition(m_Transform->X + m_Width, m_Transform->X - m_Width, m_Transform->Y, m_IsLeft);
    }

    m_RigidBody->Update( dt );
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += m_RigidBody->GetPosition().X;
    m_Collider->Set( m_Transform->X, m_Transform->Y, 32, 25 );
    if ( CollisionHandler::GetInstance()->MapCollision( m_Collider->Get() ) )
        m_Transform->X = m_LastSafePosition.X;


    m_RigidBody->Update( dt );
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->GetPosition().Y;
    m_Collider->Set( m_Transform->X, m_Transform->Y, 32, 25 );
    if ( CollisionHandler::GetInstance()->MapCollision( m_Collider->Get() ) )
    {
        m_IsGrounded = true;
        m_Transform->Y = m_LastSafePosition.Y;
    }
    else
    {
        m_IsGrounded = false;
    }

    m_Origin->X = m_Transform->X + m_Width/2;
    m_Origin->Y = m_Transform->Y + m_Height/2;
    AnimationState();
    m_Animation->Update();
    if(m_IsDead) Clean();
}

void Enemy::Clean()
{
    Texture::GetInstance()->Drop( m_TextureID );
}

void Enemy::AnimationState() {
    // idle
    m_Animation->SetProps( m_TextureID, 0, m_IdleFrame, 100);

    // running
    if(m_IsRunning) m_Animation->SetProps( m_TextureID, 0, m_IdleFrame, 250);

    // attacking
    if(m_IsAttacking) m_Animation->SetProps( m_TextureID, 1, m_AttackFrame, 100 );

    // dead
    if(m_IsDead) m_Animation->SetProps(m_TextureID, 2, m_DeadFrame, 100);
}

bool Enemy::StillAlive() {
    //return m_Index->Health != 0;
    return true;
}

void Enemy::GetHit(int DmgTaken) {
    Health -= DmgTaken;
    std::cout << "smile get hit "<< Health << std::endl;
    if(Health <= 0) m_IsDead = true;

    m_RigidBody->UnSetForce();
}
