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