#pragma once


#include <vector>
#include <raylib.h>
#include "../1_state/state.hpp"
#include "../../1_core/dataBase/dataBase.hpp"


class History : public State{
    private:
        DataBase&        dataBase;

        vector<GameData> entries;
        bool             entriesLoaded;
        int              maxEntriesToFetch;

        void loadHistory(){
            if (!entriesLoaded){
                entriesLoaded = true;
                entries       = dataBase.getHistory(maxEntriesToFetch);
            }
        }

    public:
        History(GameState& gameState, DataBase& dataBase)
        : State(gameState), dataBase(dataBase)
        {}

        void draw(){
            //
        }

        void update(){
            loadHistory();

            // exiting from history state
            if (IsKeyPressed(KEY_ENTER)){
                entriesLoaded    = false;               // so that entries will be reloaded when state again entered
                gameState        = MENU;                // return  to menu effectively
            }
        }
};