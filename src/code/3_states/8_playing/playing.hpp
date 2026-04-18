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
        SpaceShip      spaceShip; 
        Aliens         aliens;
        MotherShip     motherShip;

        int            score;
        int            enemiesDefeated;
        InputMode&     movementMode;        // for storing reference of playerInputMode from settings
        vector<Laser>& spaceShipLasers;              // for storing reference of lasers from spaceShip
        vector<Laser>& aliensLasers;

    public:
        Playing(GameState& gameState, Settings& settings) 
        : State(gameState)
        , spaceShip("1.png")
        , score(0) 
        , movementMode(settings.getMovementMode())
        , spaceShipLasers(spaceShip.getLasers())
        , aliensLasers(aliens.getLasers())
        {}

        void init(){

        }
        void draw(){
            spaceShip.draw();
            aliens.draw();
            motherShip.draw();
            // obstacles.draw();
        }
        void update(){
            spaceShip.update(movementMode, aliensLasers);
            aliens.update(spaceShipLasers, score);
            motherShip.update(spaceShipLasers, score);
            // obstacles.update();

            if (IsKeyPressed(KEY_P)){
                gameState = PAUSED;
            }
            // if (WindowShouldClose()){
            //     gameState = CLOSEGAME;
            // }
        }
};