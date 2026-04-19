#include <iostream>
#include "spaceShip.hpp"
using std::cout;


// internal, helper methods
void SpaceShip::loadShip(const string& fileName){
    spaceShip = LoadTexture(TextFormat("src/assets/graphics/player/spaceShips/%s", fileName.c_str()));
    
    // returns true if the texture is loaded into memory; alternatively coudlve used "if (spaceShip.id)"
    cout << "[GAME] SpaceShip texture (" << fileName << (IsTextureValid(spaceShip)? ") has" : ") has NOT") << " loaded properly.\n";
}
void SpaceShip::moveWASD(const int screenWidth){
    if (IsKeyDown(KEY_A)){
        posX -= speed;

        if (posX <= 0)
        {  posX = 0; }
    }
    if (IsKeyDown(KEY_D)){
        posX += speed;

        if ((posX + (spaceShip.width * scale)) >= screenWidth)
        { posX = screenWidth - (spaceShip.width * scale); }
    }
}
void SpaceShip::moveArrow(const int screenWidth){
    if (IsKeyDown(KEY_LEFT)){
        posX -= speed;

        if (posX <= 0)
        { posX = 0;  }
    }
    if (IsKeyDown(KEY_RIGHT)){
        posX += speed;

        if ((posX + (spaceShip.width * scale)) >= screenWidth)
        { posX = screenWidth - (spaceShip.width * scale); }
    }
}
void SpaceShip::moveMouse(const int screenWidth){
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        posX -= speed;

        if (posX <= 0)
        { posX = 0; }
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
        posX += speed;

        if ((posX + (spaceShip.width * scale)) >= screenWidth)
        { posX = screenWidth - (spaceShip.width * scale); }
    }
}
void SpaceShip::updateLasers(){
    for (auto it = lasers.begin(); it != lasers.end();){              // it = iterator; its similar to ptrs
        if (it->isActive()){                                          // updating laser if they active
            it->update(USER);
            ++it;
        }
        else{                                                         // removing laser if they inactive
            it = lasers.erase(it);                                    // erase returns iterator to next element
        }
    }
}
Rectangle SpaceShip::getSpaceShipRect(){
    return Rectangle{
        posX,
        posY,
        (spaceShip.width  * scale),
        (spaceShip.height * scale)
    };
}
void SpaceShip::checkCollisionWithAliensLasers(vector<Laser>& aliensLasers, int& playerLivesRemaining){
    for (auto& laser : aliensLasers){
        if (CheckCollisionRecs(getSpaceShipRect(), laser.getRect())){
            laser.deActivate();
            playerLivesRemaining--;

            if (!playerLivesRemaining){                 // ie all lives lost (reached 0)
                return;
            }
        }
    }
}

// constructor & destructor
SpaceShip::SpaceShip(const string& fileName){
    loadShip(fileName);

    scale = 0.1f;
    bottomOffset = 50;

    posX = (GetScreenWidth() / 2 - (spaceShip.width  * scale) / 2);
    posY = (GetScreenHeight()    - (spaceShip.height * scale) - bottomOffset); 

    speed = 5;
}
SpaceShip::~SpaceShip(){
    UnloadTexture(spaceShip);
}

// exposed methods
void SpaceShip::draw(){
    // DrawTexture(spaceShip, posX, posY, WHITE);                                     // doesnt allow scaling
    DrawTextureEx(spaceShip, Vector2{(float) posX, (float) posY}, 0.0f, scale, WHITE);

    for (auto &laser : lasers){
        if (laser.isActive()){
            laser.draw(); 
        }
    }
}
void SpaceShip::update(InputMode inputMode){
    int screenWidth = GetScreenWidth();

    // moving ship
    switch (inputMode)
    {
        case WASD:   { moveWASD(screenWidth);  break; }
        case ARROW:  { moveArrow(screenWidth); break; }
        case MOUSE:  { moveMouse(screenWidth); break; }
    }

    // firing lasers
    if (IsKeyPressed(KEY_SPACE)){
        lasers.push_back(Laser{(int) (posX + (spaceShip.width * scale)/2), (int) posY});
    }

    // updating lasers
    updateLasers();
}
void SpaceShip::update(InputMode inputMode, vector<Laser>& aliensLasers, int& playerLivesRemaining){
    int screenWidth = GetScreenWidth();

    // moving ship
    switch (inputMode)
    {
        case WASD:   { moveWASD(screenWidth);  break; }
        case ARROW:  { moveArrow(screenWidth); break; }
        case MOUSE:  { moveMouse(screenWidth); break; }
    }

    // firing lasers
    if (IsKeyPressed(KEY_SPACE)){
        lasers.push_back(Laser{(int) (posX + (spaceShip.width * scale)/2), (int) posY});
    }

    // updating lasers
    updateLasers();

    // checking for collisions with enemy/alien lasers
    checkCollisionWithAliensLasers(aliensLasers, playerLivesRemaining);
}

void SpaceShip::reset(){
    posX = (GetScreenWidth() / 2 - (spaceShip.width  * scale) / 2);
    posY = (GetScreenHeight()    - (spaceShip.height * scale) - bottomOffset); 
}
vector<Laser>& SpaceShip::getLasers(){
    return lasers;
}