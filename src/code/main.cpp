//                                                              بسم اللہ الرحمان الرحیم  

/*
    [Started]
        > Mar 9th, 2026

    [Finished]
        >
*/


#include <raylib.h>
#include "4_game/game.hpp"


int main()
{ 
    // open OpenGL context window
    auto windowWidth  {1080};
    auto windowHeight {720};
    auto windowName   {"Space Invaders 👾"};
    InitWindow(windowWidth, windowHeight, windowName);                 // must have this before Game game or else errors due to no openGL context
    
    // init game
    Game game;
    game.init();

    // game-loop
    while (!WindowShouldClose()){
        // updating game
        game.update();

        // drawing game
        BeginDrawing();

            game.draw();

        EndDrawing();
    }

    // uninit game
    game.close();
}