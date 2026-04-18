#pragma once


#include <vector>
#include <raylib.h>
#include "../1_state/state.hpp"
#include "../7_settings/settings.hpp"
#include "../../1_core/enums/inputMode.hpp"
#include "../../2_entities/aliens/aliens.hpp"
#include "../../2_entities/lasers/lasers.hpp"
#include "../../2_entities/spaceShip/spaceShip.hpp"
#include "../../2_entities/motherShip/motherShip.hpp"


class Playing : public State{
    private:
        SpaceShip      spaceShip;                    // composition of spaceship
        Aliens         aliens;                       // composition of aliens (swarm of alien)
        MotherShip     motherShip;                   // composition of mothership

        int            score;                        // score reached in the game session
        int            enemiesDefeated;              // total number of enemies defeated
        InputMode&     movementMode;                 // for storing reference of playerInputMode from settings
        vector<Laser>& spaceShipLasers;              // for storing reference of lasers from spaceShip
        vector<Laser>& aliensLasers;                 // reference of laser vector from aliens

    public:
        Playing(GameState& gameState, Settings& settings);

        void draw();
        void update();
};