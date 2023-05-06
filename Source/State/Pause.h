#ifndef PAUSE_H
#define PAUSE_H

#include "State.h"

class Pause: public State
{
    public:
        inline static Pause* GetInstance() { return s_Instance = ( s_Instance != nullptr ) ? s_Instance : new Pause(); }

        void Init();
        void Update();
        void Render();
        void Clean();
        void Listen();

    private:
        Pause(){}
        static Pause* s_Instance;
};

#endif // PAUSE_H
