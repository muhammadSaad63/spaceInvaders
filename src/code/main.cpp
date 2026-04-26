//                                                              بسم اللہ الرحمان الرحیم  

/*
    [Started]
        > Mar 9th, 2026

    [Finished]
        > Mar 26th, 2026
*/  


#include <raylib.h>                                                    // include raylib (the graphics library)
#include "4_game/game.hpp"                                             // for the Game class


int main()
{ 
    // open OpenGL context window
    auto windowWidth  {1080};                                          // 1080 pixels window width
    auto windowHeight {720};                                           // 720 pixels height
    auto windowName   {"Space Invaders 👾"};
    InitWindow(windowWidth, windowHeight, windowName);                 // must have this before Game game or else errors due to no openGL context
    InitAudioDevice();                                                 // opens/preps audio device 

    // init game
    Game game;                                                         // creates an object of Game class
    game.init();                                                       // initializes game

    // game-loop
    while (!WindowShouldClose()){                                      // continues while the user hasn't clicked x or preseed the esc key
        // updating game
        game.update();                                                 // updates the window based upon the current gameState 

        // drawing game
        BeginDrawing();

            game.draw();                                               // draws the window based upon the current gameState

        EndDrawing();
    }

    // uninit game
    game.close();                                                      // uninit game (mostly for memes :>)
}