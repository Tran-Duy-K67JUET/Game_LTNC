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

        void Death() {
            m_Death = true;
        }
        void GetScore(int Round, int Score) {
            r = Round;
            s = Score;
        }
    private:
        Pause(){}
        static Pause* s_Instance;
        bool m_Death;

        int r, s;
};

#endif // PAUSE_H
