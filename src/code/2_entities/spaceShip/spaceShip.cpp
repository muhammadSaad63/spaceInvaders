#include <iostream>
#include "spaceShip.hpp"
#include "../../1_core/macros/ansiColorCodes.hpp"
using std::cout;


// internal, helper methods
void SpaceShip::loadShip(const string& fileName){
    texture = LoadTexture(TextFormat("src/assets/graphics/player/spaceShips/%s", fileName.c_str()));
    
    // returns true if the texture is loaded into memory; alternatively coudlve used "if (texture.id)"
    cout << "[Captain Saad] SpaceShip texture (" << fileName << (IsTextureValid(texture)? ") has" : ") has NOT") << " loaded properly.\n";
}
void SpaceShip::moveWASD(const int screenWidth){
    if (IsKeyDown(KEY_A)){
        position.x -= horizontalSpeed;

        if (position.x <= 0)
        {  position.x = 0; }
    }
    if (IsKeyDown(KEY_D)){
        position.x += horizontalSpeed;

        if ((position.x + (texture.width * textureScale)) >= screenWidth)
        { position.x = screenWidth - (texture.width * textureScale); }
    }
}
void SpaceShip::moveArrow(const int screenWidth){
    if (IsKeyDown(KEY_LEFT)){
        position.x -= horizontalSpeed;

        if (position.x <= 0)
        { position.x = 0;  }
    }
    if (IsKeyDown(KEY_RIGHT)){
        position.x += horizontalSpeed;

        if ((position.x + (texture.width * textureScale)) >= screenWidth)
        { position.x = screenWidth - (texture.width * textureScale); }
    }
}
void SpaceShip::moveMouse(const int screenWidth){
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        position.x -= horizontalSpeed;

        if (position.x <= 0)
        { position.x = 0; }
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
        position.x += horizontalSpeed;

        if ((position.x + (texture.width * textureScale)) >= screenWidth)
        { position.x = screenWidth - (texture.width * textureScale); }
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
        position.x,
        position.y,
        (texture.width  * textureScale),
        (texture.height * textureScale)
    };
}
void SpaceShip::checkCollisionWithAliensLasers(vector<Laser>& aliensLasers, int& playerLivesRemaining){
    for (auto& laser : aliensLasers){
        if (laser.isActive() && CheckCollisionRecs(getSpaceShipRect(), laser.getRect())){
            laser.deActivate();
            playerLivesRemaining--;
            cout << "[Captain Saad] " << ANSI_BRIGHT_RED << "We lost a life! Only " << playerLivesRemaining << " remaining. :(" << ANSI_RESET << "\n"; 

            if (!playerLivesRemaining){                 // ie all lives lost (reached 0)
                return;
            }
        }
    }
}

// constructor & destructor
SpaceShip::SpaceShip(const string& fileName){
    loadShip(fileName);

    textureScale = 0.1f;
    bottomOffset = 35;

    position.x = (GetScreenWidth() / 2 - (texture.width  * textureScale) / 2);
    position.y = (GetScreenHeight()    - (texture.height * textureScale) - bottomOffset); 

    horizontalSpeed = 5;
}
SpaceShip::~SpaceShip(){
    UnloadTexture(texture);
}

// exposed methods
void SpaceShip::draw(){
    // DrawTexture(texture, position.x, position.y, WHITE);                                     // doesnt allow scaling
    DrawTextureEx(texture, Vector2{(float) position.x, (float) position.y}, 0.0f, textureScale, WHITE);

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
        lasers.push_back(Laser{(int) (position.x + (texture.width * textureScale)/2), (int) position.y});
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
        lasers.push_back(Laser{(int) (position.x + (texture.width * textureScale)/2), (int) position.y});
    }

    // updating lasers
    updateLasers();

    // checking for collisions with enemy/alien lasers
    checkCollisionWithAliensLasers(aliensLasers, playerLivesRemaining);
}

void SpaceShip::reset(){
    position.x = (GetScreenWidth() / 2 - (texture.width  * textureScale) / 2);
    position.y = (GetScreenHeight()    - (texture.height * textureScale) - bottomOffset); 
}
vector<Laser>& SpaceShip::getLasers(){
    return lasers;
}