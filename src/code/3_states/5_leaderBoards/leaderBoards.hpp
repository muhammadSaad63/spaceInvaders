#pragma once


#include "../1_state/state.hpp"


class LeaderBoards : public State{
    private:
        //

    public:
        LeaderBoards(GameState& gameState);

        void draw();
        void update();
};