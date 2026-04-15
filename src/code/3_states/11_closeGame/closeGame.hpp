#pragma once


#include "../1_state/state.hpp"


class CloseGame : public State{
    private:
        //

    public:
        CloseGame(GameState& gameState) : State(gameState) {}

        // not working
        void draw(){
            //
        }
        void update(){
            //
        }
};