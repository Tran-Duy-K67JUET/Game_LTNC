#ifndef CHOSENPHASE_H
#define CHOSENPHASE_H

#include "State.h"
#include "Player.h"

class ChosenPhase: public State {
    public:

        inline static ChosenPhase* GetInstance() { return s_Instance = ( s_Instance != nullptr ) ? s_Instance : new ChosenPhase(); }

        void Init();
        void Update();
        void Render();
        void Clean();
        void Listen();

        void SetInfor(int inf) {
            m_Infor = inf;
        }
        void SetPlayer(Player* pl) {
            m_player = pl;
        }

    private:
        ChosenPhase(){}
        Player* m_player;
        static ChosenPhase* s_Instance;
        int m_Infor;
};

#endif // CHOSENPHASE_H
