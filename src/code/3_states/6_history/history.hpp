#pragma once


#include <vector>
#include "../1_state/state.hpp"
#include "../../1_core/dataBase/dataBase.hpp"


class History : public State{
    private:
        DataBase&        dataBase;

        vector<GameData> entries;
        bool             entriesLoaded;
        int              maxEntriesToFetch;

        void loadHistory();

    public:
        History(GameState& gameState, DataBase& dataBase);

        void draw();
        void update();
};