#pragma once


#include "../1_state/state.hpp"


class History : public State{
    private:
        // DataBase& dataBase;
        // GameData& gameData;

    public:
        History(GameState& gameState) 
        : State(gameState)
        // , dataBase(dataBase)
        {}

        void draw(){

        }
        void update(){

        }
};