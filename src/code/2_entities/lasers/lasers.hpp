#pragma once


#include <raylib.h>
#include "../../1_core/enums/player.hpp"


class Laser{
    private:
        float posX;
        float posY;
        float width;
        float height;

        int   speed;
        bool  active;

        // helper functions
        void updatePlayerLaser();
        void updateAlienLaser();

    public:
        Laser(const int posX, const int posY);

        void update(Player playerType);
        void draw();

        Rectangle getRect();
        bool      isActive();
        void      deActivate();
};