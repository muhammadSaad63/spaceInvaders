#pragma once


#include <vector>
#include <string>
#include "../lasers/lasers.hpp"
#include "../../1_core/enums/inputMode.hpp"
using std::string, std::vector;


class SpaceShip{
    private:
        Texture        spaceShip;
        float          posX;
        float          posY;
        float          scale;              // the scale by which to shrink the spaceShip texture; default 0.1f
        int            bottomOffset;       // the value by which to offset/raise the ship from the bottom of the screen; default 50
        float          speed;

        vector<Laser>  lasers;

        void loadShip(const string& fileName);
        void moveWASD(const int screenWidth);
        void moveArrow(const int screenWidth);
        void moveMouse(const int screenWidth);

    public:
        SpaceShip(const string& fileName);
        ~SpaceShip();

        void draw();
        void update(InputMode inputMode, vector<Laser>& aliensLaser);

        void reset();
        vector<Laser>& getLasers();
};