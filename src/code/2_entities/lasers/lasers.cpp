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

// constructor
Laser::Laser(const int posX, const int posY) 
: posX(posX)
, posY(posY)
, width(5)
, height(25)
, speed(9)
, active(true)
{}

void Laser::update(Player playerType){
    switch (playerType)
    {
        case USER:  { updatePlayerLaser(); break; }    
        case ALIEN: { updateAlienLaser();  break; }   
    }
}
void Laser::draw(){
    DrawRectangle(posX, posY, width, height, ORANGE);
}

// utility functions
Rectangle Laser::getRect(){
    return Rectangle{posX, posY, width, height};
}
bool Laser::isActive(){
    return active;
}
void Laser::deActivate(){
    active = false;
}
