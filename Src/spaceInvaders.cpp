//                                                             بسم اللہ الرحمان الرحیم  

#include <string>
#include <raylib.h>
using std::string;

/*
    -- Feb 25:
    Started bi-idhni-Allahi Taala

    TODO
        - 
        -
meowmeow
dsa
dsa

    -- Feb 25: 
    Finished للہ الحمد کلہ :D
*/

// this is to be a simple game; just for the sake of it; say 500ish loc or less; will serve as intermediary to my main tetris

enum GameState{
    MENU,
    PLAYING,
    PAUSED,
    GAMEOVER
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

    while (!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();
} 