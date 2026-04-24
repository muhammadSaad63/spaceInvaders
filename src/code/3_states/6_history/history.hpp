#pragma once


#include <vector>
#include "../1_state/state.hpp"
#include "../../1_core/dataBase/dataBase.hpp"


class History : public State{
    private:
        DataBase&        dataBase;

        vector<GameData> history;
        bool             historyLoaded;
        int              maxEntriesToFetch;

        // drawing constants
        const int posX     { 23  };
        const int initPosY { 23  };
        const int textSize { 25  };
        const int offset   { 450 };   // gap between label and value 

        Sound     stateChangedSFX;


        void drawHeader(int& posY);
        void drawHistory(int& posY);
        void drawOverLay();

        void loadHistory();

    public:
        History(GameState& gameState, DataBase& dataBase);
        ~History();

        void draw();
        void update();
};