#include "paused.hpp"


class Paused : public State{
    private:
        Playing& playing;
        int      textSize {83};
        Sound    gameResumedSFX;
        Sound    gameStoppedSFX;

    public:
        Paused(GameState& gameState, Playing& playing) 
        : State(gameState)
        , playing(playing) 
        {
            gameResumedSFX = LoadSound("../assets/sounds/sfx/gameResumed.mp3");
            gameStoppedSFX = LoadSound("../assets/sounds/sfx/gameStopped.mp3");
        }
        ~Paused(){
            UnloadSound(gameResumedSFX);
            UnloadSound(gameStoppedSFX);
        }

        void draw(){
            // DrawText("GamePlay Paused.\n- Press \"p\" to resume.\n- Press \"x\" to finish.", GetScreenWidth() / 2 - MeasureText("GamePlay Paused.\n- Press \"p\" to resume.\n- Press \"x\" to finish.", textSize) / 2, GetScreenHeight() /2 - 3*textSize/2, textSize, GOLD);        // thats long....;  100 here is the fontsize
            DrawText("GamePlay Paused.", GetScreenWidth() / 2 - MeasureText("GamePlay Paused.", textSize) / 2, GetScreenHeight()/2 - textSize/2 - 50, textSize, GOLD);        // thats long....;  100 here is the fontsize
            DrawText("- Press \"p\" to resume.\n- Press \"x\" to finish.", GetScreenWidth() / 2 - MeasureText("- Press \"p\" to resume.\n- Press \"x\" to finish.", textSize/1.5) / 2, GetScreenHeight()/2 - textSize/2 - 50 + textSize + 30, textSize/1.5, GOLD);
        }
        void update(){
            if (IsKeyPressed(KEY_P)){
                PlaySound(gameResumedSFX);

                gameState = PLAYING;
                WaitTime(1);
            }
            if (IsKeyPressed(KEY_X)){
                PlaySound(gameStoppedSFX);
                
                gameState = MENU;
                // playing.resetAll();
                WaitTime(1);
            }
        }
};