#include "playing.hpp"


void Playing::drawScore(){
    auto color = ((gameScore < 2000)? RED : (gameScore < 5000)? YELLOW : GREEN);

    DrawText("SCORE", 50, 20, 20, RAYWHITE);
    DrawText(TextFormat("%05d", gameScore), 50, 45, 20, color);
}
void Playing::drawWaveNum(){
    auto color = ((waveNum < 10)? GREEN : waveNum < 20 ? YELLOW : RED);

    DrawText("WAVE", GetScreenWidth() - 123, 20, 20, RAYWHITE);
    DrawText(TextFormat("%02d", waveNum), GetScreenWidth() - 123, 45, 20, color);
}
void Playing::drawSeperators(){
    DrawLineEx(Vector2{30, 75}, Vector2{(float)GetScreenWidth() - 30, 75}, 2, DARKGRAY);        // upper seperator
    // DrawLineEx(Vector2{30, (float)GetScreenHeight() - 23}, Vector2{(float)GetScreenWidth() - 30, (float)GetScreenHeight() - 23}, 2, DARKGRAY);        // upper seperator
}
void Playing::drawLivesRemaining(){
    auto& texture  = spaceShip.getTexture();
    auto iconScale = 0.035;
    auto padding   = 13;

    Vector2 position;
    position.y = (GetScreenHeight() - (texture.height * iconScale) - padding);

    for (auto lifeCount {1}; lifeCount <= playerLivesRemaining; ++lifeCount){
        position.x = (padding + ((lifeCount - 1) * ((texture.width * iconScale) + padding)));

        DrawTextureEx(texture, position, 0.0f, iconScale, WHITE) ;
    }
}
void Playing::drawUI(){
    drawScore();
    drawWaveNum();
    drawSeperators();
    drawLivesRemaining();
}
float Playing::getAlpha(){
    float alpha {};

    if (announcmentTimer <= 1.0f){                            // fade in at start
        return announcmentTimer;                              // 0.0f -> 1.0f
    }
    else if (announcmentTimer <= 2.0f){                       // remain at max alpha lvl for 1s
        return 1.0f;                                          // 1.0f
    }
    else{                                                     // 2.0f < announcmentTimer <= 3.0f
        return (announcmentDuration - announcmentTimer);      // 1.0f -> 0.0f
    }
}
void Playing::announceWave(){
        string waveText = TextFormat("WAVE  %0d", waveNum);
        auto   fontSize = 90;
        auto   posX     = (GetScreenWidth() /2 - MeasureText(waveText.c_str(), fontSize)/2);
        auto   posY     = (GetScreenHeight()/2 - fontSize/2);

        float alpha = getAlpha();
        Color color = ColorAlpha(GOLD, alpha);

        DrawText(waveText.c_str(), posX, posY, fontSize, color);
}
void Playing::updateWaveAnnouncement(){
    announcmentTimer += GetFrameTime();

    if (announcmentTimer >= announcmentDuration){
        announcingWave   = false;
        announcmentTimer = 0.0f;
    }
}
void Playing::startWaveAnnouncement(){
    currWave       = waveNum;
    announcingWave = true;

    spaceShip.reset();
}

Playing::Playing(GameState &gameState, Settings &settings)
: State(gameState)
, spaceShip("1.png") 
, aliensLasers(aliens.getLasers())
, spaceShipLasers(spaceShip.getLasers())
, waveNum(aliens.getWaveNum())
, currWave(waveNum)
, movementMode(settings.getMovementMode())
{}

void Playing::draw(){
    drawUI();

    spaceShip.draw();
    aliens.draw();
    motherShip.draw();
    // obstacles.draw();

    if (announcingWave){
        announceWave();
    }
}
void Playing::update(){
    if (!playerLivesRemaining){
        gameState = GAMEOVER;
        return;
    }

    if (IsKeyPressed(KEY_P)){
        gameState = PAUSED;
        return;
    }

    if (announcingWave){
        updateWaveAnnouncement();
        return;
    }
    else if (currWave != waveNum){
        startWaveAnnouncement();
        return;
    }

    spaceShip.update(movementMode, aliensLasers, playerLivesRemaining);
    aliens.update(spaceShipLasers, gameScore, enemiesDefeated);
    motherShip.update(spaceShipLasers, gameScore, enemiesDefeated);
    // obstacles.update();
}