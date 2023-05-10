#ifndef ATTACK_H
#define ATTACK_H

#include "Vector2d.h"
#include "GameObject.h"
#include "Texture.h"

class Attack: public GameObject
{
    public:
        Attack(Properties *props, Vector2D vel): GameObject(props) {
            m_Vel = vel;
            m_animation = new Animation();
            m_animation->SetProps(props->TextureID, 0, 5, 100);
            m_Collider = new Collider();
            m_Collider->SetBuffer(0, 0, 0, 0);
        }
        void Draw() {
            m_animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Flip);
            m_Collider->DrawDebug();
        }
        void Update(float dt) {
            m_Transform->TranslateX(m_Vel.X * dt * m_IsLeft);
            m_Transform->TranslateY(m_Vel.Y * dt * m_IsLeft);
            m_animation->Update();
            m_Collider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);
        }
        void Clean() {
            Texture::GetInstance()->Drop(m_TextureID);
        }

        void SetPosition(int xr, int xl, int y, bool left) {
            if(left) {
                m_IsLeft = -1;
                m_Flip = SDL_FLIP_HORIZONTAL;
                m_Transform->X = xl;
                m_Transform->Y = y;
            } else {
                m_IsLeft = 1;
                m_Flip = SDL_FLIP_NONE;
                m_Transform->X = xr;
                m_Transform->Y = y;
            }
        }

        void SetDamage(int dmg) {
            m_Damage = dmg;
        }

        int GetDamage() {
            return m_Damage;
        }
        SDL_Rect GetBox() {return m_Collider->Get();}
    private:
        //SDL_Rect m_Box;
        Vector2D m_Vel;
        Animation* m_animation;
        int m_IsLeft;
        Collider* m_Collider;
        int m_Damage;
};

#endif // ATTACK_H
