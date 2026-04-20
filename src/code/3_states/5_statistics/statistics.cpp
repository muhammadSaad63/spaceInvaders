#pragma once


#include <raylib.h>
#include "statistics.hpp"


// internal, helper method(s)
void Statistics::loadStats(){
    if (!statsLoaded){
        stats       = dataBase.getStatistics();
        statsLoaded = true;
    }
}

Statistics::Statistics(GameState& gameState, DataBase& dataBase)
            : State(gameState), dataBase(dataBase)
            {}

void Statistics::draw(){
    //
}
void Statistics::update(){
    loadStats();

    // exiting from history state
    if (IsKeyPressed(KEY_ENTER)){
        statsLoaded = false;               // so that stats will be reloaded fresh when state is again entered
        gameState   = MENU;                // returns to menu effectively
    }
}