#pragma once


#include "../1_state/state.hpp"


class Shop : public State{
    private:
        // DataBase& dataBase;
        // GameData& gameData;

    public:
        Shop(GameState& gameState) 
        : State(gameState)
        // , dataBase(dataBase)
        {}

        void draw(){

        }
        void update(){

        }
};
