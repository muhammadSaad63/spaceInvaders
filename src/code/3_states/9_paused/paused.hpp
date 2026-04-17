#pragma once


#include <raylib.h>
#include "../1_state/state.hpp"
#include "../8_playing/playing.hpp"
#include "../../1_core/enums/gameState.hpp"


class Paused : public State{
    private:
        Playing& playing;
        int      textSize  {83};
        Sound    gameResumedSFX;
        Sound    gameStoppedSFX;

    public:
        Paused(GameState& gameState, Playing& playing);
        ~Paused();

        void draw();
        void update();
};