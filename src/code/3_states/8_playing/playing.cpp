#include "playing.hpp"


Playing::Playing(GameState& gameState, Settings& settings) 
: State(gameState)
, spaceShip("1.png")
, aliensLasers(aliens.getLasers())
, spaceShipLasers(spaceShip.getLasers())
, movementMode(settings.getMovementMode())
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

    spaceShip.update(movementMode, aliensLasers, playerLivesRemaining);
    aliens.update(spaceShipLasers, gameScore, enemiesDefeated);
    motherShip.update(spaceShipLasers, gameScore, enemiesDefeated);
    // obstacles.update();

    if (!playerLivesRemaining){
        gameState = GAMEOVER;
    }
}