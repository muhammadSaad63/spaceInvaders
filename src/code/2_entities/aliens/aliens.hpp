#pragma once


#include <array>
#include <vector>
#include <string>
#include <raylib.h>
#include "../lasers/lasers.hpp"
using std::array, std::string, std::vector;


class Alien{
    private:
        Texture2D texture;
        bool      active;

    public:
        Alien();
        ~Alien();

        void draw(const Vector2& position, const float scale);

        bool      isActive();
        void      activate();
        void      deActivate();
        float     getTextureWidth();
        float     getTextureHeight();
        Rectangle getRect(const Vector2& position, const float scale);
};


class Aliens{
    private:
        int                                   waveNum        { 0 };                                                 // the current wave num
    
        // swarm (the collection of aliens) info
        const static int                      numRows        { 3 };                                                 // the total num of rows of aliens in the swarm; dunno y but it wasnt working witout static;
        const static int                      numCols        { 5 };                                                 // the num of aliens in each row of the swarm
        array<array<Alien, numCols>, numRows> aliens;                                                               // a 2d static array of Alien(s)

        // swarm info
        Vector2                               swarmPosition  { 0, 0 };                                              // a tuple containing the (x, y) coor of the top-left point of the swarm
        int                                   swarmDirection { 1    };                                              // unit vector represeting direction of speed: 1 right, -1 left
        const int                             swarmWidth     { (alienSpacing * (numCols - 1)) + (alienSpacing) };   // the total width/length of the swarm
        
        // swarm speed
        const float                           baseSpeed      { 0.5f      };                                         // ie the min poss speed of each alien
        float                                 currSpeed      { baseSpeed };                                         // speed of each alien in the swarm in the current wave
        const float                           acceleration   { 0.15f     };                                         // ie the speed increase of each alien per wave
        
        // drawing constants
        const static int                      alienSpacing   { 81   };                                              // horizontal gap between each alien in a row
        const static int                      rowSpacing     { 70   };                                              // vertical gap between each row in the swarm
        const static int                      edgePadding    { 63   };                                              // the horizontal padding on each side of the screen
        const static float                    textureScale   { 0.1f };                                              // a float by which to scale each alien texture while drawing
        
        // lasers info
        vector<Laser>                         alienLasers    {      };                                              // a vector to store the index of active aliens in a row
        float                                 shootTimer     { 0.0f };                                              // the time passed (in s) after the last laser was shot
        float                                 shootInterval  { 2.0f };                                              // the time interval/duration bw each consecutive laser firing

        // internal, helper methods
        bool  hittingLeftEdge();
        bool  hittingRightEdge();

        void  centerSwarm();
        float calcSwarmSpeed();
        void  activateSwarm();
        bool  isSwarmDestroyed();
        void  loadNextWave();

        bool  getRandomActiveAlien(int& outRow, int& outCol);
        void  shootALaser();

    public:
        Aliens();

        void draw();
        void update();

        
        // collision: call from Playing — deactivates the alien, returns true on hit
        bool checkPlayerLaserCollision(Laser& laser);
        
        // returns alien lasers so Playing can check vs player
        vector<Laser>& getAlienLasers();
        
        int  getWaveNum();
        bool allDestroyed();

        // returns the world-space rect for alien at [row][col]
        Rectangle getAlienRect(int row, int col);
};