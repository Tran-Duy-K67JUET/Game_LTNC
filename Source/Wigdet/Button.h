#ifndef BUTTON_H
#define BUTTON_H

#include "GameObject.h"

class Button: public GameObject
{
    public:
        Button(Properties* props, int Row, int Column, float BtSize): GameObject(props) {
            m_Shape = {m_Transform->X, m_Transform->Y, m_Width * BtSize, m_Height * BtSize};
            m_IsReleased = true;
            m_Row = Row;
            m_Column = Column;
            m_Size = BtSize;
        }
        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();

        bool IsHover();
        bool IsPressed();

    private:
        bool m_IsHover;
        bool m_IsPressed;
        bool m_IsReleased;
        int m_Row, m_Column;
        SDL_Rect m_Shape;
        float m_Size;
};

#endif // BUTTON_H
