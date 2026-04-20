#pragma once


#include "../1_state/state.hpp"
#include "../../1_core/dataBase/dataBase.hpp"


class Statistics : public State{
    private:
        DataBase& dataBase;

        StatData  stats;
        bool      statsLoaded;

        void loadStats();

    public:
        Statistics(GameState& gameState, DataBase& dataBase);

        void draw();
        void update();
};