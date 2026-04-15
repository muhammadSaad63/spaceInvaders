#pragma once


#include "../1_state/state.hpp"


class GameOver : public State{
    private:
        // DataBase& dataBase;
        // GameData& gameData;

    public:
        GameOver(GameState& gameState) 
        : State(gameState)
        // , dataBase(dataBase)
        {}

        void draw(){

        }
        void update(){
            //
        }
};