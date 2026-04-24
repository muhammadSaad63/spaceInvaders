#pragma once


#include "../1_state/state.hpp"
#include "../../1_core/dataBase/dataBase.hpp"


class Statistics : public State{
    private:
        DataBase& dataBase;

        // stats stuff
        StatData  stats;
        bool      statsLoaded;

        // drawing constants
        const int posX     { 23  };
        const int initPosY { 23  };
        const int textSize { 25  };
        const int offset   { 450 };   // gap between label and value 

        Sound     stateChangedSFX;


        // drawing helpers
        void drawHeader(int& posY);
        void drawScore(int& posY);
        void drawEnemiesDefeated(int& posY);
        void drawWavesReached(int& posY);
        void drawTimePlayed(int& posY);
        void drawOverLay();

        void loadStats();

    public:
        Statistics(GameState& gameState, DataBase& dataBase);
        ~Statistics();

        void draw();
        void update();
};