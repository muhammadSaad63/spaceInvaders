#pragma once


#include <string>

// core
#include "../1_core/backGround/backGround.hpp"
#include "../1_core/dataBase/dataBase.hpp"

// states
#include "../1_core/enums/gameState.hpp"
#include "../3_states/2_menu/menu.hpp"
#include "../3_states/3_play/play.hpp"
#include "../3_states/4_shop/shop.hpp"
#include "../3_states/5_leaderBoards/leaderBoards.hpp"
#include "../3_states/6_history/history.hpp"
#include "../3_states/7_settings/settings.hpp"
#include "../3_states/8_playing/playing.hpp"
#include "../3_states/9_paused/paused.hpp"
#include "../3_states/10_gameOver/gameOver.hpp"
#include "../3_states/11_closeGame/closeGame.hpp"


class Game{
    private:
        GameState    gameState;
        BackGround   backGround;
        DataBase     dataBase;

        Settings     settings;
        Menu         menu;
        Play         play;
        Shop         shop;
        History      history;
        LeaderBoards leaderBoards;

        Playing      playing;
        Paused       paused;
        GameOver     gameOver;

        CloseGame    closeGame;

        void setFavicon(const string& fileName);
        void playEndCredits();

    public:
        Game();

        void init();

        void draw();
        void update();

        void close();                       // using this instead of ~Game()
};

