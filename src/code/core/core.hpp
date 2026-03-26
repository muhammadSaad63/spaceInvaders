#pragma once

#include <cmath>
#include <vector>
#include <raylib.h>
using std::vector;


class Grid{
    private:
        const int   cellSize;   
        const int   screenWidth;
        const int   screenHeight;

        int         fullScreenWidth;
        int         fullScreenHeight;
        bool        fullScreened;                       // holds true if the game was ever fullscreened
        
        const Color gridColor;
        const Color backgroundColor;

    public:
        Grid();

        void draw(const bool fullScreen, const bool showGrid);
};

struct Star{
    // position/size
    float centreX;              // x pos of its circular centre
    float centreY;              // y pos of its centre
    float radius;               // its radius

    // twinkling/pulsing
    float twinkleSpeed;         // the rate at which the star will blink
    float twinkleOffset;        // a random value for offsetting its twinkle/blinking
    float alpha;                // its transparency; for twinkling

    // descent/fall
    float descentSpeed;         // the speed at which the star moves downwards
};

class Stars{
    /*
        the heart of this class is the random/offsetted pulsing/twinkling of each star based upon the sine function
    */

    private:
        const int    screenWidth;
        const int    screenHeight;
        const int    numStars;              // the total count of the stars on the screen
        const float  baseAlpha;             // the min possible alpha of any star
        const float  maxAlpha;              // the max poss alpha value of a star (<= 1.0f)
        vector<Star> stars;                 // a vector array

        void generateStars();
    
    public:
        Stars();

        // i think this first time that update() is before draw()... :>
        void update();
        void draw();
};

class BackGround{
    private:
        Grid  grid;                     // background with grid
        Stars stars;                    // a collection of stars which twinkle randomly

    public:
        void draw(const bool fullScreen, const bool showGrid);
        void update();
};
