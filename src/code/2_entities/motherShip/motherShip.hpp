#pragma once


#include <vector>
#include <raylib.h>
#include "../lasers/lasers.hpp"
using std::vector;


class MotherShip{
    private:
        Texture motherShip;

        Vector2 position;           // using instead of posX, posY
        int     speed;              // speed by which to update position.x
        float   scale;

        double  lastSpawned;
        double  spawnDuration;
        bool    currentlySpawned;
        double  randomSpawnPause;   // duration after which to spawn the mothership
        bool    spawnFromLeft;      // will be randomly decided;

        int     hits;
        int     maxPossibleHits;
        int     scoreBoost;

        Rectangle getMotherShipRect();
        void      spawnMotherShip();
        void      despawnMotherShip();
        void      updateMotherShip();

    public:
        MotherShip();
        ~MotherShip();

        void draw();
        void update(vector<Laser>& lasers, int& score, int& enemiesDefeated);
};
