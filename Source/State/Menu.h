#ifndef MENU_H
#define MENU_H

#include "State.h"

class Menu: public State
{
    public:
        inline static Menu* GetInstance() { return s_Instance = ( s_Instance != nullptr ) ? s_Instance : new Menu(); }

        void Init();
        void Update();
        void Render();
        void Clean();
        void Listen();

    private:
        Menu() {}
        bool newMenu;
        static Menu* s_Instance;
};

#endif // MENU_H
