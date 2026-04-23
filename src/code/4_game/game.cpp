#include "game.hpp"
#include <raylib.h>


// helper functions
void Game::setFavicon(const string& fileName){
    Image favicon = LoadImage(TextFormat("src/assets/graphics/ui/favicons/%s", fileName.c_str()));

    if (favicon.data){
        SetWindowIcon(favicon);
        UnloadImage(favicon);
    }
}
void Game::playEndCredits(){
    double currTime     {GetTime()};
    double waitDuration {2.5};                  // in sec
    
    Sound windowCloseSFX = LoadSound("src/assets/sounds/sfx/windowClosed.mp3");
    PlaySound(windowCloseSFX);          // :

    Texture cryingCat = LoadTexture("src/assets/graphics/ui/misc/cryingCat.png");
    
    while ((currTime + waitDuration) >= GetTime()){
        backGround.update();

        BeginDrawing();
            backGround.draw(settings.isFullScreenEnabled(), settings.isGridEnabled());

            DrawTexture(cryingCat, GetScreenWidth()/2 - cryingCat.width/2, GetScreenHeight()/2 - cryingCat.height/2, ColorAlpha(RAYWHITE, 0.75f));

            // DrawText("Plz don't leave meeeee :(", GetScreenWidth()/2 - MeasureText("Plz don't leave meeeee :(", 63)/2, GetScreenHeight()/2 - 63/2, 63, GOLD);
            DrawText("Made by Ebbi, Saad, & Umair, bi-idhni-Allahi Taala :>", 23, GetScreenHeight() - 23 - 5, 23, GOLD);
        EndDrawing();
        // WaitTime(2.5);
    }

    UnloadSound(windowCloseSFX);
}

// constructor
Game::Game()                        // overRiding default constructor 
: gameState(MENU)                   // initializing gameState with MENU
, settings(gameState)               // constructed first & before menu since the later requires it
, menu(gameState, settings)
, play(gameState)
, shop(gameState) 
, history(gameState, dataBase)
, statistics(gameState, dataBase)
, playing(gameState, settings)
, paused(gameState, playing)
, gameOver(gameState, dataBase, playing)
, closeGame(gameState) 
{}

void Game::init(){
    SetWindowOpacity(0.9);
    SetExitKey(KEY_ESCAPE);
    SetTargetFPS(60); // why would you set it to 63 what is wrong with you
    // InitAudioDevice();

    setFavicon("1.png");
}

void Game::draw(){                                                    // draws based upon the current gameState
    backGround.draw(settings.isFullScreenEnabled(), settings.isGridEnabled());

    switch(gameState)
    {
        case MENU:         { menu.draw();         break; }
        case PLAY:         { play.draw();         break; }
        case SHOP:         { shop.draw();         break; }
        case HISTORY:      { history.draw();      break; }
        case STATISTICS:   { statistics.draw();   break; }
        case SETTINGS:     { settings.draw();     break; }
        case PLAYING:      { playing.draw();      break; }
        case PAUSED:       { paused.draw();       break; }
        case GAMEOVER:     { gameOver.draw();     break; }
        case CLOSEGAME:    { closeGame.draw();    break; }  
    }
}
void Game::update(){     
    backGround.update();
    
    // updates based upon the current gameState
    switch(gameState)
    {
        case MENU:         { menu.update();         break; }
        case PLAY:         { play.update();         break; }
        case SHOP:         { shop.update();         break; }
        case HISTORY:      { history.update();      break; }
        case STATISTICS:   { statistics.update();   break; }
        case SETTINGS:     { settings.update();     break; }
        case PLAYING:      { playing.update();      break; }
        case PAUSED:       { paused.update();       break; }
        case GAMEOVER:     { gameOver.update();     break; }
        case CLOSEGAME:    { closeGame.update();    break; }  
    }
}

// using this instead of ~Game()
void Game::close(){
    playEndCredits();
    
    CloseAudioDevice();
    CloseWindow();
}