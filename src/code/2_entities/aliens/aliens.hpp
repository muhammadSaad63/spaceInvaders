#pragma once


#include <vector>
#include <raylib.h>
using std::vector;


class Alien{
    private:
        int     posX;
        int     posY;
        int     row;
        int     col;
        bool    active;
        Texture alien;
        float   scale;

    public:
        Alien();

        void draw();
        void update();
};
class Aliens{
    private:
        vector<vector<Alien>> aliens;               // 2D array of Alien

    public:

        void draw();
        void update();
};