#pragma once


#include <vector>
#include <raylib.h>
#include "../lasers/lasers.hpp"
using std::vector;


class MotherShip{
    private:
        Texture motherShip;

        Vector2 position;           // using instead of posX, posY
        float   speed;              // speed by which to update position.x
        float   scale;

        double  lastSpawned;
        bool    currentlySpawned;
        double  randomSpawnPause;   // duration after which to spawn the mothership
        bool    spawnFromLeft;      // will be randomly decided;
        int     edgePadding;

        int     hits;
        int     maxPossibleHits;
        int     scoreBoost;

        Rectangle getMotherShipRect();
        void      spawnMotherShip();
        bool      reachedEdge();
        void      despawnMotherShip();
        void      checkForHits(vector<Laser>& spaceShipLasers, int& gameScore, int& enemiesDefeated);
        void      updateMotherShipPosition();

    public:
        MotherShip();
        ~MotherShip();

        void draw();
        void update(vector<Laser>& spaceShipLasers, int& gameScore, int& enemiesDefeated);
};
