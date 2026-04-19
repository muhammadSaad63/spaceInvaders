#include "lasers.hpp"


// helper functions
void Laser::updatePlayerLaser(){
    posY -= speed;                                  // if the user fired the laser, decrease its posX by speed (ie move it up)
    if (posY <= 0){
        deActivate();
        // cout << "[GAME] Laser deactivated!\n";
    }
}
void Laser::updateAlienLaser(){
    posY += speed;                                  // if the aliens fired the laser, increase its posX by speed (ie move it down)
    if ((posY + height) >= GetScreenHeight()){
        deActivate();
    }
}
void Laser::drawExplosion(){
    auto minRadius   = 1.0f;
    auto maxRadius   = 5.0f;
    auto scale       = ((GetTime() - explosionStartTime)/explosionDuration);          // 0.0f -> 1.0f
    auto outerRadius = (minRadius + (maxRadius * scale)); 

    DrawCircle((posX + width/2), posY, outerRadius, GOLD);                            // a larger, outer circle
    DrawCircle((posX + width/2), posY, minRadius, RAYWHITE);                          // a small inner circle
}

// constructor
Laser::Laser(const int posX, const int posY) 
    : posX(posX)
    , posY(posY)
    , width(5)
    , height(25)
    , speed(9)
    , active(true)
    , exploding(false)
    , explosionDuration(0.5f)
    {}

void Laser::update(Player playerType){
    if (exploding){
        if ((GetTime() - explosionStartTime) >= explosionDuration){
            exploding = false;
        }

        return;
    }

    switch (playerType)
    {
        case USER:  { updatePlayerLaser(); break; }    
        case ALIEN: { updateAlienLaser();  break; }   
    }
}
void Laser::draw(){
    if (exploding){
        drawExplosion();
        return;
    }

    if (active){
        DrawRectangle(posX, posY, width, height, ORANGE);
        return;
    }
}

// utility functions
Rectangle Laser::getRect(){
    return Rectangle{posX, posY, width, height};
}
bool Laser::isAlive(){
    return (active || exploding);
}
bool Laser::isActive(){
    return (active && !exploding);
}
void Laser::deActivate(){
    active = false;

    // remove below code to disable explosions
    if ((posY > 0) && ((posY + height) < GetScreenHeight())){              // laser will explode only if the laser did not reach the screen edge
        exploding          = true;
        explosionStartTime = GetTime();
    }
}
