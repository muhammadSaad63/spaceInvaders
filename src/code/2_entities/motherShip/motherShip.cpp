#include <iostream> 
#include "motherShip.hpp"
#include "../../1_core/macros/ansiColorCodes.hpp"
using std::cout;


// internal methods
Rectangle MotherShip::getMotherShipRect(){
    return Rectangle{position.x, position.y, (float)(motherShip.width * scale), (float)(motherShip.height * scale)};
}
void MotherShip::spawnMotherShip(){
    currentlySpawned = true;
    hits = 0;
    lastSpawned = GetTime(); 

    spawnFromLeft = (bool)GetRandomValue(0, 1);                                              // true if 1 generated, false if not
    position.x = ((spawnFromLeft)? 0 : (GetScreenWidth() - (motherShip.width * scale)));
    
    if (speed < 0){ speed *= -1; }   
}
bool MotherShip::reachedEdge()
{
    if (spawnFromLeft){
        return ((position.x + (motherShip.width * scale)) >= GetScreenWidth());
    } 
    else{
        return (position.x <= 0);
    }
}
void MotherShip::despawnMotherShip()
{
    currentlySpawned = false;
    randomSpawnPause = GetRandomValue(20, 40);              // will spawn after a random n seconds (n > 20, < 40)
    lastSpawned = GetTime();
}
void MotherShip::checkForHits(vector<Laser>& spaceShipLasers, int& gameScore, int& enemiesDefeated){
    for (auto& laser : spaceShipLasers){
        if (laser.isActive() && CheckCollisionRecs(laser.getRect(), getMotherShipRect())){
            laser.deActivate();
            hits++;

            if (hits >= maxPossibleHits){
                despawnMotherShip();

                gameScore += scoreBoost;
                enemiesDefeated++;

                cout << "[Captain Saad] " << ANSI_BRIGHT_GREEN << "The MotherShip has been blown to smithereens! :D" << ANSI_RESET << "\n";
                // playsound

                return;
            }
        }
    }
}
void MotherShip::updateMotherShipPosition(){
    if (spawnFromLeft){
        position.x += speed;

        if ((position.x + motherShip.width * scale) >= GetScreenWidth()){
            speed *= -1;
        }
    }
    else{
        position.x -= speed;

        if (position.x <= 0){
            speed *= -1;
        }
    }
}

// construcor & destructor
MotherShip::MotherShip() 
: lastSpawned(0)                                                // time when the ship last spawned; initialized with the 0/getTime()
, currentlySpawned(false)                                       // is the motherShip currently spawned            
, hits(0)                                                       // number of hits currently sustained by the motherShip
, maxPossibleHits(9)                                            // max number of hits to defeat/destruct the motherShip
, scoreBoost(1000)                                              // 1000 extra points on destruction
, motherShip(LoadTexture("src/assets/graphics/enemies/motherShips/1.png"))
, position({0.0f, 35})
, scale(0.125f)
, randomSpawnPause(30)                                          // 30s
, speed(1.25f)
, spawnFromLeft(true)
{}
MotherShip::~MotherShip(){
    if (IsTextureValid(motherShip))                             // this check is redundant tho...
    { UnloadTexture(motherShip);  }
}

// exposed methods
void MotherShip::draw(){
    if (currentlySpawned){
        DrawTextureEx(motherShip, position, 0.0f, scale, WHITE);
        DrawText(TextFormat("%d", maxPossibleHits - hits), position.x + (motherShip.width * scale)/2 - 5, position.y, 20 , GOLD);
    }
}
void MotherShip::update(vector<Laser>& spaceShipLasers, int& gameScore, int& enemiesDefeated){
    if (currentlySpawned)
    {
        // despawning if it has reached the edge
        if (reachedEdge()){            
            despawnMotherShip();

            cout << "[Captain Saad] " << ANSI_BRIGHT_RED << "The MotherShip has warped into the cosmos :(" << ANSI_RESET << "\n";
            // playsound...

            return;
        }

        // checking for hits
        checkForHits(spaceShipLasers, gameScore, enemiesDefeated);

        // updating position
        updateMotherShipPosition();
    }

    else
    {
        if (GetTime() >= (lastSpawned + randomSpawnPause)){
            spawnMotherShip();
            
            cout << "[Captain Saad] " << ANSI_BRIGHT_GREEN << "An alien motherShip has warped into our space! :D" << ANSI_RESET << "\n";
            // playsound...
        }
    }
}