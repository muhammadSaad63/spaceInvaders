//                                                             بسم اللہ الرحمان الرحیم  

#include <string>
#include <raylib.h>
using std::string;

/*
    [Started]
        >

    [Abstract]
        >

    TODO
        - 
        -

    [Finished]
        >
*/


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
        CLOSEWINDOW             // when user chooses to close the window; plays a meme or similar
};
enum InputMode{                 // an ENUM to indicate the chosen playerInputMode (altered in settings)
    WASD,                       
    ARROW,                      
    MOUSE
};

class State{                                    // an abstract class to be inheriteed by all gameState subclasses
    protected:
        GameState& gameState;

    public:
        State(GameState& gameState) : gameState(gameState) {}

        virtual void draw() = 0;

        virtual void update() = 0;
};
class Menu : public State{
    private:
        //

    public:
        Menu(GameState& gameState) : State(gameState) {}

        void draw(){

        }
        void update(){

        }
};
class Playing : public State{
    private:
        //

    public:
        Playing(GameState& gameState) : State(gameState) {}

        void draw(){

        }
        void update(){

        }
};
class Paused : public State{
    private:
        //

    public:
        Paused(GameState& gameState) : State(gameState) {}

        void draw(){

        }
        void update(){

        }
};
class GameOver : public State{
    private:
        //

    public:
        GameOver(GameState& gameState) : State(gameState) {}

        void draw(){

        }
        void update(){

        }
};
class Game{
    private:
        GameState gameState;

        Menu     menu;
        Playing  playing;
        Paused   paused;
        GameOver gameOver;


    public:
        Game() 
        : gameState(MENU)
        , menu(gameState)
        , playing(gameState)
        , paused(gameState)
        , gameOver(gameState) {}

        void draw(){
            switch(gameState)
            {
                case MENU:     { menu.draw();     break; }
                case PLAYING:  { playing.draw();  break; }
                case PAUSED:   { paused.draw();   break; }
                case GAMEOVER: { gameOver.draw(); break; }
            }
        }
        void update(){
            switch(gameState)
            {
                case MENU:     { menu.update();     break; }
                case PLAYING:  { playing.update();  break; }
                case PAUSED:   { paused.update();   break; }
                case GAMEOVER: { gameOver.update(); break; }
            }
        }
};


int main()
{
    InitWindow(1080, 720, "Space Invaders 👾");
    SetWindowOpacity(0.9);
    SetExitKey(KEY_ESCAPE);

    Image favicon = LoadImage("Assets/Favicon/11.png");
    if (favicon.data){
        SetWindowIcon(favicon);
        UnloadImage(favicon);
    }

    Game game;

    while (!WindowShouldClose()){
        // updating
        game.update();

        // drawing
        BeginDrawing();

            ClearBackground(BLACK);
            game.draw();
        
        EndDrawing();
    }

    CloseWindow();
}