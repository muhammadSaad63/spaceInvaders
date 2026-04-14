//                                                             بسم اللہ الرحمان الرحیم  

#include <cmath>               // for sine, PI
#include <string>
#include <cctype>               // for isalpha, islower
#include <vector>
#include <iostream>
#include <raylib.h>
#include <stdlib.h>             // for toupper
#include "core/core.hpp"
#include <SQLiteCpp/SQLiteCpp.h>
using std::cout, std::string, std::vector;


/*
    [Abstract]
        >


    [Started]
        > Mar 9th, 2026

    [Finished]
        >
*/


// Main ---

int main()
{
    // init
    InitWindow(1080, 720, "Space Invaders 👾");                 // must have this before Game game or else errors due to no openGL context
    
    Game game;
    game.init();

    while (!WindowShouldClose()){
        // updating
        game.update();

        // drawing
        BeginDrawing();

            game.draw();

        EndDrawing();
    }

    // uninit
    game.close();
}