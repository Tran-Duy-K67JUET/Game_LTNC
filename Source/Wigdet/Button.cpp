#include "Button.h"
#include "Input.h"
#include "Texture.h"

void Button::Draw()
{
    Texture::GetInstance()->DrawButton(m_TextureID, m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Row, m_Column, m_Size);
}

void Button::Update(float dt)
{
    Vector2D mPos = Input::GetInstance()->GetMousePosition();
    SDL_Point point = {mPos.X, mPos.Y};
    m_IsPressed = false;
    if(SDL_PointInRect(&point, &m_Shape)) {
        if(Input::GetInstance()->GetMouseDown() && m_IsReleased) {
            m_IsPressed = true;
            m_IsHover = false;
            m_IsReleased = false;
        } else if(!Input::GetInstance()->GetMouseDown()) {
            m_IsReleased = true;
            m_IsHover = true;
            m_IsPressed = false;
        }
    } else {
        m_IsReleased = true;
        m_IsHover = false;
        m_IsPressed = false;
    }
}

void Button::Clean()
{
    Texture::GetInstance()->Drop(m_TextureID);
}

bool Button::IsHover()
{
    return m_IsHover;
}

bool Button::IsPressed()
{
    return m_IsPressed;
}


