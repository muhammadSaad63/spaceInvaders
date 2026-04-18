#include "playing.hpp"


Playing::Playing(GameState& gameState, Settings& settings) 
: State(gameState)
, spaceShip("1.png")
, score(0) 
, movementMode(settings.getMovementMode())
, spaceShipLasers(spaceShip.getLasers())
, aliensLasers(aliens.getLasers())
{}

void Playing::draw(){
    spaceShip.draw();
    aliens.draw();
    motherShip.draw();
    // obstacles.draw();
}
void Playing::update(){
    spaceShip.update(movementMode, aliensLasers);
    aliens.update(spaceShipLasers, score);
    motherShip.update(spaceShipLasers, score);
    // obstacles.update();

    if (IsKeyPressed(KEY_P)){
        gameState = PAUSED;
    }
}
