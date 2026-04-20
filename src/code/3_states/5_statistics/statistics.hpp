#pragma once


#include "../1_state/state.hpp"


class Statistics : public State{
    private:
        //

    public:
        Statistics(GameState& gameState);

        void draw();
        void update();
};