#pragma once


enum GameState{                 // an ENUM to indicate the current state of the game
    // mainMenu
        MENU,                   // the mainMenu screen of the game; contains the following 👇
            PLAY,               // contains options such as playerName, difficulty, spaceShip skin etc
            SHOP,               // buy diff spaceShip skins, aliens' skins, SFX perhaps
            HISTORY,            // show gameHistory (using sqlite)
            LEADERBOARDS,       // display leaderBoards with top10 players (using sqlite)
            SETTINGS,           // game settings such as fullscreen, SFX volume, playerInputMode, opacity etc (similar to Mr. Pong's)

    // gamePlay
        PLAYING,                // actual gamePlay state
        PAUSED,                 // while game is paused inside PLAYING
        GAMEOVER,               // when game ends inside PLAYING; shows outcome, score, aliens-defeated, coins earned etc

    // windowShouldClose()
        CLOSEGAME               // when user chooses to close the window; plays a meme or similar
};