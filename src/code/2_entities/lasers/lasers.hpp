#pragma once


#include <raylib.h>
#include "../../1_core/enums/player.hpp"


class Laser{
    private:
        float posX;
        float posY;
        float width;
        float height;

        int     speed;
        bool    active;

        bool  exploding;
        float explosionDuration;
        float explosionStartTime;

        // helper functions
        void updatePlayerLaser();
        void updateAlienLaser();
        void drawExplosion();

    public:
        Laser(const int posX, const int posY);

        void update(Player playerType);
        void draw(Player playerType);

        Rectangle getRect();
        bool      isAlive();
        bool      isActive();
        void      deActivate();
};