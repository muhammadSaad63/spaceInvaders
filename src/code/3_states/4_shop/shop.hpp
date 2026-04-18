#pragma once


#include "../1_state/state.hpp"


class Shop : public State{
    private:
        //

    public:
        Shop(GameState& gameState);

        void draw();
        void update();
};