#pragma once


#include "../1_state/state.hpp"
#include "../../1_core/dataBase/dataBase.hpp"
#include "../../1_core/enums/gameState.hpp"


class GameOver : public State{
    private:
        DataBase& dataBase;
        // GameData& gameData;

    public:
        GameOver(GameState& gameState, DataBase& dataBase) 
        : State(gameState)
        , dataBase(dataBase)
        {}

        void draw(){

        }
        void update(){
            //
        }
};