#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"
#include <string>

class Character : public GameObject {
    public:
        Character( Properties* props ): GameObject( props ) {}
        virtual void Draw()=0;
        virtual void Update( float dt )=0;
        virtual void Clean()=0;
        Transform* GetTrans() {
            return m_Transform;
        }
        int GetHealth() {
            return Health;
        }
    protected:
        std::string m_Name;
        int Health;

};

#endif // CHARACTER_H
