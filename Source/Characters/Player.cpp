#include <SDL2/SDL.h>
#include "Player.h"
#include "Texture.h"
#include "Input.h"
#include "Camera.h"
#include "CollisionHandler.h"
#include "Attack.h"
#include "EnemyManager.h"
#include "Pause.h"
#include "Engine.h"
#include "Sound.h"

Attack* Player::m_CurrentAttack = nullptr;

Player::Player( Properties* props ): Character(props)
{
    m_IsAttacking = false;
    m_IsFalling = false;
    m_IsGrounded = false;
    m_IsJumping = false;
    m_IsPunching = false;
    m_IsRunning = false;
    m_IsShoot = false;
    m_IsLeft = false;

    m_Flip = SDL_FLIP_NONE;
    m_AttackTime = ATTACK_TIME;
    m_JumpTime = JUMP_TIME;
    m_Jump_Force = JUMP_FORCE;
    m_CoolDown = 0;


    m_Collider = new Collider();
    m_Collider->SetBuffer( -40, -15, 80, 20 );

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity( 9.8f );

    m_Animation = new Animation();
    Health = 10;
    Slash = 1;
    Shoot = 2;
}

void Player::Draw()
{
    m_Animation->Draw( m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Flip );
    m_Collider->DrawDebug();
    if(m_CurrentAttack != nullptr) m_CurrentAttack->Draw();
}

void Player::Update(float dt)
{
    m_IsRunning = false;
    m_RigidBody->UnSetForce();
    m_CoolDown -= dt;

    // idle state
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
        m_IsLeft = true;
        m_Flip = SDL_FLIP_HORIZONTAL;
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {

        m_IsLeft = false;
        m_Flip = SDL_FLIP_NONE;
    }

    // run forward
    if( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D) && !m_IsAttacking && !m_IsFalling ) {
        m_RigidBody->ApplyForceX( FORWARD * RUN_FORCE );
        m_IsRunning = true;
    }

    // run backward
    if( Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) && !m_IsAttacking && !m_IsFalling) {
        m_RigidBody->ApplyForceX( BACKWARD * RUN_FORCE );
        m_IsRunning = true;
    }

    // attack
    if( Input::GetInstance()->GetKeyDown( SDL_SCANCODE_F ) )
    {
        m_RigidBody->UnSetForce();
        m_IsAttacking = true;
        SetCurrentAttack(new Attack(new Properties("Slash", 100, 100, 37, 50), (0, 0), Slash));
        m_CurrentAttack->SetPosition(m_Transform->X+60, m_Transform->X+3,m_Transform->Y+17, m_IsLeft);
    }

    // punching
    if( Input::GetInstance()->GetKeyDown( SDL_SCANCODE_Q ))
    {
        m_RigidBody->UnSetForce();
        m_IsPunching = true;
        m_IsShoot = true;
        SetCurrentAttack(new Attack(new Properties("Shoot", m_Transform->X, m_Transform->Y + 30, 63, 32), (7, 7), Shoot));
        m_CurrentAttack->SetPosition(m_Transform->X +60, m_Transform->X -30, m_Transform->Y +20, m_IsLeft);
    }

    // jumping
    if ( Input::GetInstance()->GetKeyDown( SDL_SCANCODE_W ) && m_IsGrounded )
    {
        m_IsJumping = true;
        m_IsGrounded = false;
        m_RigidBody->ApplyForceY( UPWARD*m_Jump_Force );
    }
    if ( Input::GetInstance()->GetKeyDown( SDL_SCANCODE_W ) && m_IsJumping && m_JumpTime > 0 )
    {
        m_JumpTime -= dt;
        m_RigidBody->ApplyForceY(UPWARD*m_Jump_Force);
    }
    else
    {
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME;
    }

    // falling
    if(m_RigidBody->GetVelocity().Y > 0 && !m_IsGrounded) m_IsFalling = true;
    else m_IsFalling = false;

    // attack timer
    if(m_IsAttacking && m_AttackTime > 0 && m_CoolDown <= 0) {
        m_AttackTime -= dt;
        if(m_CurrentAttack != nullptr) m_CurrentAttack->Update(dt);
    } else {
        if(m_AttackTime <= 0) m_CoolDown = COOL_DOWN;
        m_IsAttacking = false;
        m_AttackTime = ATTACK_TIME;
    }

    if(m_IsPunching) Sound::GetInstance()->PlayeEffect("Shoot");
    if(m_IsAttacking) Sound::GetInstance()->PlayeEffect("Slash");

    // punch timer
    if(m_IsPunching && m_PunchTime > 0 && m_CoolDown <= 0) {
        m_PunchTime -= dt;
    } else {
        if(m_PunchTime <= 0) m_CoolDown = COOL_DOWN;
        m_IsPunching = false;
        m_PunchTime = PUNCH_TIME;
    }

    //Shoot timer
    if(m_IsShoot && m_ShootTime > 0) {
        m_ShootTime -= dt;
        if(m_CurrentAttack != nullptr) m_CurrentAttack->Update(dt);
    } else {
        if(m_CurrentAttack != nullptr) m_CurrentAttack->Moving(false);
        m_IsShoot = false;
        m_ShootTime = SHOOT_TIME;
    }

    m_RigidBody->Update( dt );
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += m_RigidBody->GetPosition().X;
    m_Collider->Set( m_Transform->X, m_Transform->Y, 100, 74 );
    if ( CollisionHandler::GetInstance()->MapCollision( m_Collider->Get() ) )
        m_Transform->X = m_LastSafePosition.X;

    m_RigidBody->Update( dt );
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->GetPosition().Y;
    m_Collider->Set( m_Transform->X, m_Transform->Y, 100, 74 );
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
    if(Health <=0) DeadStatment();
}

void Player::Clean()
{
    Texture::GetInstance()->Drop( m_TextureID );
}

void Player::GetHit() {
    Health--;
    std::cout << Health << std::endl;
}

void Player::DeadStatment() {
    Engine::GetInstance()->ChangeState(Pause::GetInstance());
    Pause::GetInstance()->Death();
}

void Player::AnimationState() {
    // idle
    m_Animation->SetProps( m_TextureID, 3, 4, 100);

    // running
    if(m_IsRunning) m_Animation->SetProps( m_TextureID, 7, 6, 60);

    // attacking
    if(m_IsAttacking) m_Animation->SetProps( m_TextureID, 4, 5, 50);

    // jumping
    if(m_IsJumping) m_Animation->SetProps( m_TextureID, 2, 3, 200 );

    // falling
    if(m_IsFalling) m_Animation->SetProps( m_TextureID, 0, 2, 200 );

    // punching
    if(m_IsPunching) m_Animation->SetProps(m_TextureID, 8, 5, 60);
}

void Player::UseItems(int Type, int inf) {
    switch (Type) {
    case 1:
        Health += inf;
        break;
    case 2:
        Slash += inf;
        break;
    case 3:
        Shoot += inf;
        break;
    }
}
