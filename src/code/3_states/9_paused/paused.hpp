#pragma once


#include "../1_state/state.hpp"
#include "../8_playing/playing.hpp"


class Paused : public State{
    private:
        Playing& playing;
        Sound    gameResumedSFX;
        Sound    gameStoppedSFX;
        int      textSize { 50 };

    public:
        Paused(GameState& gameState, Playing& playing);
        ~Paused();

        void draw();
        void update();
};