#include <raylib.h>
#include "history.hpp"


// helpers
void History::loadHistory(){
    if (!entriesLoaded){
        entriesLoaded = true;
        entries       = dataBase.getHistory(maxEntriesToFetch);
    }
}

History::History(GameState& gameState, DataBase& dataBase)
: State(gameState), dataBase(dataBase)
{}

void History::draw(){
    //
}
void History::update(){
    loadHistory();

    // exiting from history state
    if (IsKeyPressed(KEY_ENTER)){
        entriesLoaded    = false;               // so that entries will be reloaded when state again entered
        gameState        = MENU;                // return  to menu effectively
    }
}
