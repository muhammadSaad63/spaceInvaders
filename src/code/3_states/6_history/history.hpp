#pragma once


#include "../1_state/state.hpp"


class History : public State{
    private:
        //

    public:
        History(GameState& gameState);

        void draw();
        void update();
};