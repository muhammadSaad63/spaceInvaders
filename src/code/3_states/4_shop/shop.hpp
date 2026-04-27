#pragma once


#include <raylib.h>
#include "../1_state/state.hpp"


class Shop : public State{
    private:
        Texture wowSoEmpty;                     // the (dog) meme image
        Sound   shopWowSFX;                     // the waow sound
        bool    memePlayed;                     // so that the sound plays only once when gameState entered

    public:
        Shop(GameState& gameState);
        ~Shop();

        void draw();
        void update();
};