#include "playing.hpp"


Playing::Playing(GameState& gameState, Settings& settings) 
: State(gameState)
, spaceShip("1.png")
, score(0) 
, enemiesDefeated(0)
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
    if (IsKeyPressed(KEY_P)){
        gameState = PAUSED;
    }

    spaceShip.update(movementMode, aliensLasers);
    aliens.update(spaceShipLasers, score, enemiesDefeated);
    motherShip.update(spaceShipLasers, score, enemiesDefeated);
    // obstacles.update();

}
