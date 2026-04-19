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
        Aliens         aliens;                              // composition of aliens (swarm of alien)
        SpaceShip      spaceShip;                           // composition of spaceship
        MotherShip     motherShip;                          // composition of mothership

        InputMode&     movementMode;                        // for storing reference of playerInputMode from settings
        vector<Laser>& aliensLasers;                        // reference of laser vector from aliens
        vector<Laser>& spaceShipLasers;                     // for storing reference of lasers from spaceShip

        bool           playingCountdown       {true};
        float          elapsedCountdownTime   {0.0f};
        float          totalCountdownDuration {4.0f};           // 3, 2, 1; dunno y but 3.0f wasnt working

        bool           announcingWave          {true};
        float          announcmentDuration     {3.0f};         // 3 sec        
        float          elapsedAnnouncementTime {0.0f};

        // implement starting countdown, laser particle effects, alien proper edge bounce logic, gameOver logic, lasers should not pass thru menuButtons even when one is selected

        int&           waveNum;
        int            currWave;
        int            gameScore            {0};            // score reached in the game session
        int            enemiesDefeated      {0};            // total number of enemies defeated
        int            playerLivesRemaining {3};            // the number of player/spaceShip lives remaining


        // draw helpers
        void  drawCountdown();
        void  drawScore();
        void  drawWaveNum();
        void  drawSeperators();
        void  drawLivesRemaining();
        void  drawUI();

        // update helpers
        void  updateCountdown();
        float getAlpha();
        void  announceWave();
        void  updateWaveAnnouncement();
        void  startWaveAnnouncement();

    public:
        Playing(GameState& gameState, Settings& settings);

        void draw();
        void update();
};