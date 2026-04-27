#pragma once


#include <raylib.h>
#include "../1_state/state.hpp"


class Shop : public State{
    private:
        Texture wowSoEmpty;
        bool    memePlayed;

    public:
        Shop(GameState& gameState);
        ~Shop();

        void draw();
        void update();
};