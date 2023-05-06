#ifndef PLAY_H
#define PLAY_H

#include "State.h"
#include "GameMap.h"

class Play: public State
{
    public:
        inline static Play* GetInstance() { return s_Instance = ( s_Instance != nullptr ) ? s_Instance : new Play(); }

        void Init();
        void Update();
        void Render();
        void Clean();
        void Listen();

        inline GameMap* GetMap() {return m_LevelMap;}

    private:
        Play(){}
        static Play* s_Instance;
        GameMap* m_LevelMap;
        bool m_PauseGame;
};

#endif // PLAY_H
