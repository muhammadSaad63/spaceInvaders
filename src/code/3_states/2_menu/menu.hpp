#pragma once


#include <string>
#include <raylib.h>
#include "../1_state/state.hpp"
#include "../7_settings/settings.hpp"
#include "../../1_core/enums/gameState.hpp"
#include "../../1_core/enums/inputMode.hpp"
#include "../../2_entities/spaceShip/spaceShip.hpp"
using std::string;


struct MenuIcon{
    Rectangle rect;
    string    text;
    int       textSize;
    GameState gameState;
};

class MenuIcons{
    private:
        MenuIcon  icons[5];
        bool      selected;
        double    selectedTime;
        double    selectedDelay;                    // in sec
        GameState selectedState;

    public:
        MenuIcons();

        void draw();
        GameState update(SpaceShip& spaceShip);
};

class Menu : public State{
    private:
        MenuIcons  icons;                    // a group of 5 icons/button
        SpaceShip  spaceShip;                // the spaceShip at the bottom
        InputMode& movementMode;             // for input mode

    public:
        Menu(GameState& gameState, Settings& settings);

        void draw();
        void update();
};