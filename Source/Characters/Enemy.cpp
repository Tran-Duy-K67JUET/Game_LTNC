#include <SDL.h>
#include "Enemy.h"
#include "Texture.h"
#include "Input.h"
#include "Camera.h"
#include "CollisionHandler.h"
#include <iostream>

Enemy::Enemy(Properties* props, int AttackFrame, int IdleFrame, int DeadFrame): Character(props)
{
    m_AttackFrame = AttackFrame;
    m_IdleFrame = IdleFrame;
    m_DeadFrame = DeadFrame;


    m_IsAttacking = false;
    m_IsRunning = false;
    m_IsGrounded = false;
    m_IsLeft = false;

    m_Flip = SDL_FLIP_NONE;
    m_AttackTime = ATTACK_TIME;
    m_RunTime = MOVE_TIME;
    m_IdleTime = IDLE_TIME;

    m_Collider = new Collider();
    m_Collider->SetBuffer( 0, 0, 0, 0);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity( 9.8f );

    m_Animation = new Animation();
}

void Enemy::Draw()
{
    m_Animation->Draw( m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Flip );
    m_Collider->DrawDebug();
}

void Enemy::Update(float dt)
{
    m_IsRunning = false;
    m_RigidBody->UnSetForce();

    //random number


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
    if(m_IsAttacking) m_Animation->SetProps( m_TextureID, 1, m_AttackFrame, 60 );
}
