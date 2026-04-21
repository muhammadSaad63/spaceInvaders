#pragma once


#include "../1_state/state.hpp"
#include "../8_playing/playing.hpp"
#include "../../1_core/enums/gameState.hpp"
#include "../../1_core/dataBase/dataBase.hpp"


class GameOver : public State{
    private:
        DataBase& dataBase;
        Playing&  playing;
        float     timer;

        Sound     stateChangedSFX;

    public:
        GameOver(GameState& gameState, DataBase& dataBase, Playing& playing);
        ~GameOver();

        void draw();
        void update();
};