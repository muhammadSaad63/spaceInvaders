#include "playing.hpp"
#include <cmath>
using std::ceilf, std::fmodf;


void Playing::loadSounds(){
    countDown321 = LoadSound("src/assets/sounds/sfx/countDown321.mp3");
}
void Playing::unloadSounds(){
    UnloadSound(countDown321);
}

void Playing::drawCountdown(){
    auto  secondProgress = fmodf(elapsedCountdownTime, 1.0f);                        // how much of the corr second has passed
    auto  displayNum     = static_cast<int>( ceilf(totalCountdownDuration - elapsedCountdownTime) );
    auto  fontSize       = static_cast<int>( 350 - (150.0f * secondProgress) );             // font size shrinks as each seconds passes and then maximizes
    auto  alpha          = static_cast<float>(  1.0f - (secondProgress * 0.35f) );         // 1.0 → 0.65
    Color baseColor      = ((displayNum  == 3)? RED : (displayNum == 2)? YELLOW : GREEN);
    auto  text           = TextFormat("%d", displayNum);


    DrawText(text, (GetScreenWidth()/2 - MeasureText(text, fontSize)/2), (GetScreenHeight()/2 - fontSize/2), fontSize, ColorAlpha(baseColor, alpha));
}
void Playing::drawScore(){
    auto color = ((gameScore < 10000)? RED : (gameScore < 50000)? YELLOW : GREEN);

    DrawText("SCORE", 50, 20, 20, RAYWHITE);
    DrawText(TextFormat("%06d", gameScore), 50, 45, 20, color);
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
    auto iconScale = 0.035f;
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

void Playing::updateCountdown(){
    elapsedCountdownTime += GetFrameTime();

    if (elapsedCountdownTime >= totalCountdownDuration){
        playingCountdown = false;
        return;
    }
}
float Playing::getAlpha(){
    float alpha {};

    if (elapsedAnnouncementTime <= 1.0f){                            // fade in at start
        return elapsedAnnouncementTime;                              // 0.0f -> 1.0f
    }
    else if (elapsedAnnouncementTime <= 2.0f){                       // remain at max alpha lvl for 1s
        return 1.0f;                                          // 1.0f
    }
    else{                                                     // 2.0f < elapsedAnnouncementTime <= 3.0f
        return (totalAnnouncementDuration - elapsedAnnouncementTime);      // 1.0f -> 0.0f
    }
}
void Playing::announceWave(){
        string waveText = TextFormat("WAVE  %02d", waveNum);
        auto   fontSize = 90;
        auto   posX     = (GetScreenWidth() /2 - MeasureText(waveText.c_str(), fontSize)/2);
        auto   posY     = (GetScreenHeight()/2 - fontSize/2);

        float alpha = getAlpha();
        Color color = ColorAlpha(GOLD, alpha);

        DrawText(waveText.c_str(), posX, posY, fontSize, color);
}
void Playing::updateWaveAnnouncement(){
    elapsedAnnouncementTime += GetFrameTime();

    if (elapsedAnnouncementTime >= totalAnnouncementDuration){
        announcingWave   = false;
        elapsedAnnouncementTime = 0.0f;
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
        , motherShip(aliens.getWaveNum())
        , currWave(waveNum)
        , movementMode(settings.getMovementMode())
{
    loadSounds();
}
Playing::~Playing(){
    unloadSounds();
}

void Playing::draw(){
    if (playingCountdown){
        drawCountdown();
        return;
    }

    drawUI();                   // move this below the announcingWave block below if u no wanna make the ui visible while waveAnnouncments

    if (announcingWave){
        announceWave();
        return;
    }

    spaceShip.draw();
    aliens.draw();
    motherShip.draw();
    // obstacles.draw();
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

    if (playingCountdown){
        updateCountdown();
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

void Playing::reset(){
    gameScore               = { 0 };
    enemiesDefeated         = { 0 };
    playerLivesRemaining    = { 3 };

    playingCountdown        = { true };
    elapsedCountdownTime    = { 0.0f };
    announcingWave          = { true };
    elapsedAnnouncementTime = { 0.0f };

    spaceShip.reset();
    // motherShip.reset();
    // aliens.reset();
}