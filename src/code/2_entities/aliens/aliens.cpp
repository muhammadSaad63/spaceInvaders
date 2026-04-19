#include <utility>
#include <iostream>
#include "aliens.hpp"
using std::cout, std::pair;


Alien::Alien() 
: active(true)
{
    texture = {};
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
void  Alien::activate()         { active = true;  }
void  Alien::deActivate()       { active = false; }

void Alien::loadAlien(const string& fileName){
    texture = LoadTexture(TextFormat("src/assets/graphics/enemies/aliens/%s", fileName.c_str()));
}
float Alien::getTextureWidth(){ 
    return static_cast<float>(texture.width);  
}
float Alien::getTextureHeight(){ 
    return static_cast<float>(texture.height); 
}
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

void Aliens::loadAliens(const string &fileName){
    for (auto& row : aliens){
        for (auto& alien : row){
            alien.loadAlien(fileName);
        }
    }
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
    
    if (waveNum == 1){
        loadAliens("1.png");
    }

    activateSwarm();
    centerSwarm();
    currSpeed = calcSwarmSpeed();

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
void Aliens::updateLasers(){
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
bool Aliens::checkSpaceShipLaserCollision(Laser& spaceShipLaser){
    if (!spaceShipLaser.isActive()) { return false; }

    for (auto row {0}; row < numRows; ++row){
        for (auto col {0}; col < numCols; ++col){
            if (!aliens[row][col].isActive()) { continue; }

            if (CheckCollisionRecs(spaceShipLaser.getRect(), getAlienRect(row, col))){
                aliens[row][col].deActivate();
                spaceShipLaser.deActivate();

                return true;                // one laser can only hit one alien
            }
        }
    }

    return false;
}
int Aliens::checkSpaceShipLasersCollision(vector<Laser>& spaceShipLasers){
    auto aliensDefeated {0};

    for (auto& laser : spaceShipLasers){
        if (checkSpaceShipLaserCollision(laser)){
            aliensDefeated++;
        }
    }

    return aliensDefeated;                      // no alien died; yayyyyyyyyy
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

void Aliens::update(vector<Laser>& spaceShipLasers, int& score, int& enemiesDefeated)
{
    if (isSwarmDestroyed()){
        loadNextWave();

        cout << "[Captain Saad] Alien Swarm - " << waveNum << " was successfully vanquished :D\n";
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
    updateLasers();

    // checking for collision with spaceship's lasers
    auto aliensDefeated = checkSpaceShipLasersCollision(spaceShipLasers);
    enemiesDefeated += aliensDefeated;
    score += (aliensDefeated * scoreBoost);
}

vector<Laser>& Aliens::getLasers(){
    return lasers;
}
int  Aliens::getWaveNum()      { return waveNum; }