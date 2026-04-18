// #include <array>
// #include <string>
// #include <vector>
// #include <raylib.h>
// // #include "lasers.hpp"
// using std::array, std::string, std::vector;

// enum Player{
//     USER,                       // used to refer to the user/player/human
//     ALIEN                       // used to refer to the enemy/computer/pc/alien(s)
// };

// class Laser{
//     private:
//         float posX;
//         float posY;
//         float width;
//         float height;

//         int   speed;
//         bool  active;

//         // helper functions
//         void updatePlayerLaser();
//         void updateAlienLaser();

//     public:
//         Laser(const int posX, const int posY);

//         void update(Player playerType);
//         void draw();

//         Rectangle getRect();
//         bool      isActive();
//         void      deActivate();
// };

// // helper functions
// void Laser::updatePlayerLaser(){
//     posY -= speed;                                  // if the user fired the laser, decrease its posX by speed (ie move it up)
//     if (posY <= 0){
//         deActivate();
//         // cout << "[GAME] Laser deactivated!\n";
//     }
// }
// void Laser::updateAlienLaser(){
//     posY += speed;                                  // if the aliens fired the laser, increase its posX by speed (ie move it down)
//     if ((posY + height) >= GetScreenHeight()){
//         deActivate();
//     }
// }
// // constructor
// Laser::Laser(const int posX, const int posY) 
// : posX(posX)
// , posY(posY)
// , width(5)
// , height(25)
// , speed(9)
// , active(true)
// {}
// void Laser::update(Player playerType){
//     switch (playerType)
//     {
//         case USER:  { updatePlayerLaser(); break; }    
//         case ALIEN: { updateAlienLaser();  break; }   
//     }
// }
// void Laser::draw(){
//     DrawRectangle(posX, posY, width, height, ORANGE);
// }
// // utility functions
// Rectangle Laser::getRect(){
//     return Rectangle{posX, posY, width, height};
// }
// bool Laser::isActive(){
//     return active;
// }
// void Laser::deActivate(){
//     active = false;
// }


// class Alien{
//     private:
//         Texture2D texture;
//         bool      active;

//         void loadAlien(const string& fileName){
//             texture = LoadTexture(fileName.c_str());
//         }

//     public:
//         Alien() : active(true)
//         { texture = LoadTexture("1.png"); }
//         ~Alien(){
//             if (texture.id){
//                 UnloadTexture(texture);
//             }
//         }

//         void draw(const Vector2& position, const float& scale){
//             DrawTextureEx(texture, position, 0.0f, scale, WHITE);
//         }

//         float getTextureWidth(){
//             return (texture.height);
//         }
//         float getTextureHeight(){
//             return (texture.height);
//         }
//         bool isActive(){
//             return active;
//         }
//         void activate(){
//             if (!active)
//             { active = true; }
//         }
//         void deActivate(){
//             if (active)
//             { active = false; }
//         }
// };

// class Aliens{
//     private:
//         const static int                        numRows   { 3 };
//         const static int                        numAliens { 5 };                                                   // dunno u but was not working without static
//         array<array<Alien, numAliens>, numRows> aliens;                                                          // 2D array of Alien
//         const float                             scale     { 0.1f };
        
//         const int edgePadding    { 63 };                                                                           // on one side
//         const int alienSpacing   { 81 };
//         // const int alienSpacing { (GetScreenWidth() - (padding_X * 2)) / numAliens };
//         // const int alienSpacing { (aliens[0][0].getTexture().width  * scale) + 13 };
//         const int rowSpacing     { 70 };
//         // const int rowSpacing   { (aliens[0][0].getTexture().height * scale) + 13 };

//         Vector2   swarmPosition  { 0, 0 };
//         int       swarmDirection { 1 };                                                                                 // 1 right, -1 left
//         const int swarmWidth     { (alienSpacing * (numAliens - 1)) + (alienSpacing) };
//         // const int swarmWidth { (alienSpacing * (numAliens - 1)) + (aliens[0][0].getTexture().width) };

//         int         waveNum      { 0 };                   // the current wave num
//         const float baseSpeed    { 0.5f };                // ie the min poss speed of each alien
//         float       currSpeed    { baseSpeed };           // speed of each alien in the swarm in the current wave
//         const float acceleration { 0.15f };               // ie the speed increase of each alien per wave
        
//         vector<Laser> lasers;
//         float shootTimer      { 0.0f };                     // stores number of secs passed since last laser shot                 
//         float shootInterval   { 2.0f };                     // the number of sec after which to shoot another laser
//         float lastCheckedTime {};

//         // internal, helper methods
//         bool hittingLeftEdge(){
//             return (swarmPosition.x <= edgePadding);
//         }
//         bool hittingRightEdge(){
//             return ((swarmPosition.x + swarmWidth) >= (GetScreenWidth() - edgePadding));
//         }

//         void centerSwarm(){
//             swarmPosition.x = ((GetScreenWidth() - swarmWidth) / 2);
//             swarmPosition.y = 63;
//         }
//         float calcSwarmSpeed(){
//             return (baseSpeed + ((waveNum - 1) * acceleration));
//         }
//         void activateSwarm(){
//             for (auto& rowOfAliens : aliens){
//                 for (auto& alien : rowOfAliens){
//                     alien.activate();
//                 }
//             }
//         }
//         bool isSwarmDestroyed(){
//             for (auto& rowOfAlien : aliens){
//                 for (auto& alien : rowOfAlien){
//                     if (alien.isActive()){
//                         return false;
//                     }
//                 }   
//             }

//             return true;
//         }
//         void loadNextWave(){
//             waveNum++;                              // increments waveNum

//             currSpeed = calcSwarmSpeed();           // calculates new current speed and assigns the value to currSpeed

//             activateSwarm();                        // set active status of all aliens to true

//             centerSwarm();                          // centers the alien swarm across the screen
//         }
//         bool hasSecondPassed(const float& currTime){
//             return ((currTime - lastCheckedTime) >= 1.0f);
//         }
//         void getRandomActiveAlien(int& rowNum, int& alienNum){
//             vector<int> activeAliens;
//             activeAliens.reserve(numAliens);

//             auto col {0};

//             for (auto row {2}; row >= 0; --row){
//                 activeAliens.clear();

//                 col = 0;
//                 for (col < numAliens; ++col){
//                     if (aliens[row][col].isActive()){
//                         activeAliens.push_back(col);
//                     }
//                 }

//                 if (activeAliens.size() > 0){
//                     auto alienToShoot = GetRandomValue(0, activeAliens.size() - 1);
                    
//                     rowNum   = row;
//                     alienNum = col;

//                     return;
//                 }
//             }
//         }
//         void shoot(){
//             if (shootTimer >= shootInterval){
//                 // choose random alien adn shoot
//                 int rowNum, alienNum;
//                 getRandomActiveAlien(rowNum, alienNum);
                
//                 auto posX = (swarmPosition.x + (alienSpacing * alienNum) + aliens[rowNum][alienNum].getTextureWidth()/2);
//                 auto posY = (swarmPosition.y + (rowNum * rowSpacing) + aliens[rowNum][alienNum].getTextureHeight());
//                 lasers.push_back(Laser{ posX, posY });

//                 shootTimer = 0;
//                 shootInterval = static_cast<float>(GetRandomValue(2, 8) / 2.0f);               // sets timer for the next laser shooting as a random value bw 1 & 4 (inclusive)
//             }
//             else{ 
//                 auto currTime = GetTime();

//                 if (hasSecondPassed(currTime)){
//                     shootTimer++;
//                 }
                
//                 lastCheckedTime = currTime;
//             }
//         }


//     public:
//         Aliens(){
//             loadNextWave();
//         }

//         void draw(){
//             Vector2 position {};

//             for (auto rowNum {0}; rowNum < numRows; ++rowNum){
//                 for (auto alienNum {0}; alienNum < numAliens; ++alienNum){
//                     position.x = (swarmPosition.x + (alienSpacing * alienNum));
//                     position.y = (swarmPosition.y + (rowNum * rowSpacing));

//                     aliens[rowNum][alienNum].draw(position, scale);
//                 }
//             }
//         }
//         void update(){
//             if (isSwarmDestroyed()){
//                 loadNextWave();

//                 return;
//             }

//             if (hittingLeftEdge() || hittingRightEdge()){
//                 swarmDirection *= -1;
//                 swarmPosition.y += (rowSpacing / 3);
//             }

//             swarmPosition.x += (currSpeed * swarmDirection);
//         }

//         Rectangle getAlienRect(const int& rowNum, const int& alienNum){
//             return Rectangle{
//                             (swarmPosition.x + ((alienNum - 1) * alienSpacing)),
//                             (swarmPosition.y + ((alienNum - 1) * rowSpacing)),
//                             (aliens[rowNum][alienNum].getTextureWidth()  * scale),
//                             (aliens[rowNum][alienNum].getTextureHeight() * scale)
//             };
//         }
//         int& getWaveNum(){
//             return waveNum;
//         }
// };


// int main(){
//     InitWindow(1080, 720, "test");
//     SetTargetFPS(60);

//     Aliens a;

//     while (!WindowShouldClose()){
//         a.update();

//         BeginDrawing();

//             ClearBackground(BLANK);
//             a.draw();  

//         EndDrawing();  
//     }

//     CloseWindow();
// }


#include <utility>
#include "aliens.hpp"
using std::pair;


Alien::Alien() 
: active(true)
{
    texture = LoadTexture("../assets/graphics/aliens/1.png");
}
Alien::~Alien(){
    if (texture.id){
        UnloadTexture(texture);
    }
}

void Alien::draw(const Vector2& position, const float scale){
    if (active){
        DrawTextureEx(texture, position, 0.0f, scale, WHITE);
    }
}

bool  Alien::isActive()         { return active;  }
void  Alien::activate()         { if (!active) active = true;  }
void  Alien::deActivate()       { if (active)  active = false; }

float Alien::getTextureWidth()  { return static_cast<float>(texture.width);  }
float Alien::getTextureHeight() { return static_cast<float>(texture.height); }
Rectangle Alien::getRect(const Vector2& position, const float scale){
    return Rectangle{
        position.x,
        position.y,
        texture.width  * scale,
        texture.height * scale
    };
}


// aliens internal, helper methods
bool Aliens::hittingLeftEdge(){
    return (swarmPosition.x <= edgePadding);
}
bool Aliens::hittingRightEdge(){
    return ((swarmPosition.x + swarmWidth) >= (GetScreenWidth() - edgePadding));
}

void Aliens::centerSwarm(){
    swarmPosition.x = static_cast<float>((GetScreenWidth() - swarmWidth) / 2);
    swarmPosition.y = 63.0f;
}
float Aliens::calcSwarmSpeed(){
    return (baseSpeed + ((waveNum - 1) * acceleration));
}
void Aliens::activateSwarm(){
    for (auto& row : aliens){
        for (auto& alien : row){
            alien.activate();
        }
    }
}
bool Aliens::isSwarmDestroyed(){
    for (auto& row : aliens){
        for (auto& alien : row){
            if (alien.isActive()){
                return false;
            }
        }
    }

    return true;
}
void Aliens::loadNextWave(){
    waveNum++;
    currSpeed = calcSwarmSpeed();

    activateSwarm();
    centerSwarm();

    lasers.clear();
    shootTimer    = 0.0f;
    shootInterval = 2.0f;
}

bool Aliens::getRandomActiveAlien(int& outRow, int& outCol){
    vector<pair<int,int>> candidates;
    candidates.reserve(numCols);

    for (int col = 0; col < numCols; ++col){
        for (int row = numRows - 1; row >= 0; --row){                       // finding the bottomost active alien in this particular col of swarm
            if (aliens[row][col].isActive()){
                candidates.push_back(pair{ row, col });

                break;
            }
        }
    }

    if (candidates.empty()){                                                // no active aliens
        return false;
    }

    auto randIndex = GetRandomValue(0, static_cast<int>(candidates.size()) - 1);
    outRow         = candidates[randIndex].first;
    outCol         = candidates[randIndex].second;

    return true;
}

void Aliens::shootALaser(){
    shootTimer += GetFrameTime();                                                 // time bw drawing of last frame and curr one

    if (shootTimer < shootInterval){                                              // there still time until shooting duration passed/overcome
        return;
    }

    shootTimer    = 0.0f;
    shootInterval = (static_cast<float>(GetRandomValue(100, 400)) / 100.0f);      // a random float bw 1.0 – 4.0 s

    int row, col;
    if (!getRandomActiveAlien(row, col)){
        return;                                                                   // no active aliens left (isSwarmDestroyed() will be true)
    }

    // xpawning laser from the bottom-centre of the chosen alien
    float laserX = swarmPosition.x
                 + (col * alienSpacing)
                 + ((aliens[row][col].getTextureWidth() * textureScale) / 2.0f);                            // add half the width of texture
    float laserY = swarmPosition.y
                 + (row * rowSpacing)
                 + (aliens[row][col].getTextureHeight() * textureScale);                                    // add full height of texture

    lasers.push_back(Laser{ static_cast<int>(laserX), static_cast<int>(laserY) });
}


Aliens::Aliens(){
    loadNextWave();
}

void Aliens::draw(){
    // Draw aliens
    Vector2 position;

    for (int row = 0; row < numRows; ++row){
        for (int col = 0; col < numCols; ++col){
            if (aliens[row][col].isActive()){
                position.x = (swarmPosition.x + (col * alienSpacing));
                position.y = (swarmPosition.y + (row * rowSpacing  ));

                aliens[row][col].draw(position, textureScale);
            }
        }
    }

    // Draw alien lasers
    for (auto& laser : lasers){
        if (laser.isActive()){
            laser.draw();
        }
    }
}

void Aliens::update(){
    if (isSwarmDestroyed()){
        loadNextWave();

        return;
    }

    // move aliens' swarm
    if (hittingLeftEdge() || hittingRightEdge()){
        swarmDirection  *= -1;                                                  // reversing direc
        swarmPosition.y += static_cast<float>(rowSpacing) / 3.0f;               // moving down when hit edge
    }
    swarmPosition.x += currSpeed * swarmDirection;

    // fire a laser if can
    shootALaser();

    // updating active lasers
    for (auto it = lasers.begin(); it != lasers.end();){                  // using it as iterator
        if (it->isActive()){
            it->update(ALIEN);
            ++it;
        } 
        else{
            it = lasers.erase(it);                                     // removing inactive lasers
        }
    }
}

Rectangle Aliens::getAlienRect(int row, int col){
    Vector2 position{
        swarmPosition.x + (col * alienSpacing),
        swarmPosition.y + (row * rowSpacing)
    };

    return aliens[row][col].getRect(position, textureScale);
}

bool Aliens::checkPlayerLaserCollision(Laser& laser){
    if (!laser.isActive()) return false;

    for (int row = 0; row < numRows; ++row){
        for (int col = 0; col < numCols; ++col){
            if (!aliens[row][col].isActive()) continue;

            if (CheckCollisionRecs(laser.getRect(), getAlienRect(row, col))){
                aliens[row][col].deActivate();
                laser.deActivate();
                return true;                // one laser can only hit one alien
            }
        }
    }
    return false;
}

vector<Laser>& Aliens::getLasers(){
    return lasers;
}

int  Aliens::getWaveNum()      { return waveNum; }
bool Aliens::areAllDestroyed() { return isSwarmDestroyed(); }