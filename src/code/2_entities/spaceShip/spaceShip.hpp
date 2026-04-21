#pragma once


#include <vector>
#include <string>
#include "../lasers/lasers.hpp"
#include "../../1_core/enums/inputMode.hpp"
using std::string, std::vector;


class SpaceShip{
    private:
        Texture texture;
        Vector2 position;
        float   textureScale;                                                                                  // the scale by which to shrink the spaceShip texture; default 0.1f
        int     bottomOffset;                                                                                  // the value by which to offset/raise the ship from the bottom of the screen; default 50
        float   horizontalSpeed;
        Sound   laserFiredSFX;

        vector<Laser>  lasers;

        void      loadShip(const string& fileName);
        void      moveWASD(const int screenWidth);
        void      moveArrow(const int screenWidth);
        void      moveMouse(const int screenWidth);
        void      updateLasers();
        Rectangle getSpaceShipRect();
        void      checkCollisionWithAliensLasers(vector<Laser>& aliensLasers, int& playerLivesRemaining);

    public:
        SpaceShip(const string& fileName);
        ~SpaceShip();

        void draw();
        void update(InputMode inputMode);                                                                   // overloading update; one for main, other for playing
        void update(InputMode inputMode, vector<Laser>& aliensLasers, int& playerLivesRemaining);

        void reset();
        vector<Laser>& getLasers();
        Texture&       getTexture();
};