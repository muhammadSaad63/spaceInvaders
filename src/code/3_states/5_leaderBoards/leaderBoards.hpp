#pragma once


#include "../1_state/state.hpp"


class LeaderBoards : public State{
    private:
        // DataBase& dataBase;
        // GameData& gameData;

    public:
        LeaderBoards(GameState& gameState) 
        : State(gameState)
        // , dataBase(dataBase)
        {}

        void draw(){

        }
        void update(){

        }
};