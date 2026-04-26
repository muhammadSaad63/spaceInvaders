#pragma once


#include <string>

// core
#include "../1_core/dataBase/dataBase.hpp"
#include "../1_core/backGround/backGround.hpp"

// states
#include "../1_core/enums/gameState.hpp"
#include "../3_states/2_menu/menu.hpp"
#include "../3_states/3_play/play.hpp"
#include "../3_states/4_shop/shop.hpp"
#include "../3_states/5_statistics/statistics.hpp"
#include "../3_states/6_history/history.hpp"
#include "../3_states/7_settings/settings.hpp"
#include "../3_states/8_playing/playing.hpp"
#include "../3_states/9_paused/paused.hpp"
#include "../3_states/10_gameOver/gameOver.hpp"
#include "../3_states/11_closeGame/closeGame.hpp"


class Game{
    private:
        GameState    gameState;                                // an enum which holds the current gameState 

        BackGround   backGround;                               // a class which manages the starry background
        DataBase     dataBase;                                 // a class which manages the programData.db database

        Settings     settings;                                 // used to alter various game settings such as volume, opacity, and fullScreen
        Menu         menu;                                     // the mainMenu
        Play         play;                                     // a buffer state between menu & playing; not implemented;
        Shop         shop;                                     // a place where players could use "coins" to get various stuff; not implemented;
        History      history;                                  // displays gameHistory using dataBase
        Statistics   statistics;                               // displays stats using dataBase

        Playing      playing;                                  // the main gamePlay manager class
        Paused       paused;                                   // when the player press P during playing
        GameOver     gameOver;                                 // reached after the player spaceShip loses all 3 of its lives in playing

        CloseGame    closeGame;                                // was to be used instead of playEndCredits() but couldnt be implemented

        void setFavicon(const string& fileName);               // opens, sets, and then closes favicon image; used by init()
        void playEndCredits();                                 // a helper method used by close()

    public:
        Game();                                                // default constructor which constructs all the above attributes

        void init();                                           // initializes game window; called before gameLoop in main.cpp

        void draw();                                           // draws based upon the current gameState
        void update();                                         // updates based upon the current gameState

        void close();                                          // called when windowShouldClose is true after gameLoop; using this instead of ~Game()
};