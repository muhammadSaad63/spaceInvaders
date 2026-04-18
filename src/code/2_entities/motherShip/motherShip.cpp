#include <iostream> 
#include "motherShip.hpp"
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
void MotherShip::despawnMotherShip(){
    currentlySpawned = false;
    randomSpawnPause = GetRandomValue(20, 40);              // will spawn after a random n seconds (n > 20, < 40)
    lastSpawned = GetTime();
}
void MotherShip::updateMotherShip(){
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
, spawnDuration(15)                                             // will appear for a duration of 15s
, currentlySpawned(false)                                       // is the motherShip currently spawned            
, hits(0)                                                       // number of hits currently sustained by the motherShip
, maxPossibleHits(7)                                            // max number of hits to defeat/destruct the motherShip
, scoreBoost(1000)                                              // 1000 extra points on destruction
, motherShip(LoadTexture("src/assets/graphics/enemies/motherShips/1.png"))
, position({0.0f, 50})
, scale(0.15f)
, randomSpawnPause(30)                                          // 30s
, speed(2)
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
void MotherShip::update(vector<Laser>& lasers, int& score){
    if (currentlySpawned)
    {
        // despawning if it has spawned for >= spawnDuration time
        if (GetTime() >= (lastSpawned + spawnDuration)){            
            despawnMotherShip();

            cout << "[Game] Despawning motherShip (time over)\n";
            // playsound...

            return;
        }

        // checking for hits
        for (auto& laser : lasers){
            if (laser.isActive() && CheckCollisionRecs(laser.getRect(), getMotherShipRect())){
                laser.deActivate();
                hits++;

                if (hits >= maxPossibleHits){
                    despawnMotherShip();

                    score += scoreBoost;
                    cout << "[Game] motherShip Destructed\n";
                    // playsound

                    return;
                }
            }
        }

        // updating position
        updateMotherShip();
    }

    else
    {
        if (GetTime() >= (lastSpawned + randomSpawnPause)){
            spawnMotherShip();
            
            cout << "[Game] Spawning motherShip\n";
            // playsound...
        }
    }
}