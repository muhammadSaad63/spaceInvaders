/*                                                      بسم اللہ الرحمان الرحیم  


    [Abstract]
        >


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
    auto screenWidth  {1080};
    auto screenHeight {720};
    InitWindow(screenWidth, screenHeight, "Space Invaders 👾");                 // must have this before Game game or else errors due to no openGL context
    
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