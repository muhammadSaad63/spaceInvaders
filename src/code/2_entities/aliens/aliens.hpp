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

        void      loadAlien(const string& fileName);
        float     getTextureWidth();
        float     getTextureHeight();
        Rectangle getRect(const Vector2& position, const float scale);
};


class Aliens{
    private:
        int                                   waveNum        { 0 };                                                 // the current wave num
    
        // swarm formation
        const static int                      numRows        { 3 };                                                 // the total num of rows of aliens in the swarm; dunno y but it wasnt working witout static;
        const static int                      numCols        { 5 };                                                 // the num of aliens in each row of the swarm
        array<array<Alien, numCols>, numRows> aliens;                                                               // a 2d static array of Alien(s)

        // swarm info
        Vector2                               swarmPosition  { 0, 0 };                                              // a tuple containing the (x, y) coor of the top-left point of the swarm
        int                                   swarmDirection { 1    };                                              // unit vector represeting direction of speed: 1 right, -1 left
        const int                             swarmWidth     { (alienSpacing * (numCols - 1)) + (alienSpacing) };   // the total width/length of the swarm
        const int                             scoreBoost     { 50   };                                              // the increment in the session's score upon defeating a alien

        // swarm speed
        const float                           baseSpeed      { 0.5f      };                                         // ie the min poss speed of each alien
        float                                 currSpeed      { baseSpeed };                                         // speed of each alien in the swarm in the current wave
        const float                           acceleration   { 0.15f     };                                         // ie the speed increase of each alien per wave
        
        // drawing constants
        int                                   alienSpacing   { 81   };                                              // horizontal gap between each alien in a row
        int                                   rowSpacing     { 70   };                                              // vertical gap between each row in the swarm
        int                                   edgePadding    { 63   };                                              // the horizontal padding on each side of the screen
        float                                 textureScale   { 0.1f };                                              // a float by which to scale each alien texture while drawing
        
        // lasers info
        vector<Laser>                         lasers         {      };                                              // a vector to store the index of active aliens in a row
        float                                 shootTimer     { 0.0f };                                              // the time passed (in s) after the last laser was shot
        float                                 shootInterval  { 2.0f };                                              // the time interval/duration bw each consecutive laser firing

        // internal, helper methods
        bool  hittingLeftEdge();                                                                                    // returns true if the left end of the swarm is hitting the left edge of the screen
        bool  hittingRightEdge();                                                                                   // returns true if the right end of the swarm is hitting the right edge of the screen                                                                  

        void  centerSwarm();                                                                                        // positions the swarm at the centre of the window (for the start of each wave)
        float calcSwarmSpeed();                                                                                     // calculates and returns the swarmSpeed for the current waveNum
        void  activateSwarm();                                                                                      // sets all the aliens in the swarm to active
        void  loadNextWave();                                                                                       // makes use of the above 3 helper methods to bring about the next wave
        bool  isSwarmDestroyed();                                                                                   // returns true if all the aliens in the swarm in the current wave are destroyed

        bool  getRandomActiveAlien(int& outRow, int& outCol);                                                       // sets the arguments to the relevant data of the first alien in the swarm (bottom-up) which is active (to shoot lasers from)
        void  shootALaser();         
        void  updateLasers();                                                                               // shoots a laser from an active alien in the swarm

        Rectangle getAlienRect(int row, int col);
        bool      checkSpaceShipLaserCollision(Laser& laser);
        int       checkSpaceShipLasersCollision(vector<Laser>& spaceShipLasers);

    public:
        Aliens();

        void draw();
        void update(vector<Laser>& spaceShipLasers, int& score, int& enemiesDefeated);

        int            getWaveNum();                                                                                // getter for waveNum
        vector<Laser>& getLasers();                                                                                 // getter for the lasers vector
};