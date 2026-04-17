#pragma once


#include <string>
#include <raylib.h>
#include "../1_state/state.hpp"
#include "../../1_core/enums/gameState.hpp"
#include "../../1_core/enums/inputMode.hpp"
using std::string;


class Settings : public State{
    // copied from your Mr.Pong game - ebbi

    private:
        bool         enableFullScreen      {false};         // setwindowstate(FLAG_BORDERLESS_WINDOWED_MODE); ClearWindowState(); SetWindowSize();
        bool         enableGrid        {true};          // whether to show the background grid or not
        int          frameRate       {60};            // again, why 63.
        float        windowOpacity   {0.9f};
        float        masterVolume    {0.5};
        InputMode    playerInputMode {WASD};

        const int    posX            {23};
        const int    initPosY        {23};          // the y value at which to start drawing
        int          posY            {};
        const int    textSize        {35};
        const int    offSet          {100};             // gap between text/heading and option/toggler
        const Color  color           {GOLD};
        const string texts[6]        {"   > enableFullScreen     ", "   > Grid              ", "   > FrameRate     ", "   > Window Opacity", "   > SFX Volume    ", "   > Input Mode    "};

        Sound settingModifySFX;

        // internal, helper functions
        int getPosY(const auto& index){
            return (initPosY + ((index - 1) * offset) + ((enableFullScreen && index == 2)? 63 : 0));
        }

        void drawHeader(const auto& index){
            posY = getPosY(index);

            DrawText("Settings", posX, posY, 53, GOLD);
        }
        void drawFullScreen(const auto& index){
            posY = getPosY(index);

            DrawText(texts[0].c_str(), posX, posY, textSize, color);
            DrawText(TextFormat("%s", (enableFullScreen)? "Enabled" : "Disabled"), posX + MeasureText(texts[0].c_str(), textSize) + 100, posY, textSize, (enableFullScreen)? GREEN : RED);
        }
        void drawGrid(const auto& index){
            posY = getPosY(index);

            DrawText(texts[1].c_str(), posX, posY, textSize, color);
            DrawText(TextFormat("%s", (enableGrid)? "Enabled" : "Disabled"), posX + MeasureText(texts[1].c_str(), textSize) + 100, posY, textSize, (enableGrid)? GREEN : RED);

        }
        void drawFrameRate(const auto& index){
            posY = getPosY(index);

            DrawText(texts[2].c_str(), posX, posY, textSize, color);
            DrawText(TextFormat("%d", frameRate), posX + MeasureText(texts[2].c_str(), textSize) + 100, posY, textSize, (frameRate == 23)? RED : (frameRate == 40)? ORANGE : (frameRate == 63)? YELLOW : GREEN);
        }
        void drawWindowOpacity(const auto& index){
            posY = getPosY(index);

            DrawText(texts[3].c_str(), posX, posY, textSize, color);
            DrawText(TextFormat("%.1f", windowOpacity), posX + MeasureText(texts[3].c_str(), textSize) + offSet, posY, textSize, (windowOpacity <= 0.4)? RED : (windowOpacity <= 0.7)? YELLOW : GREEN);
        }
        void drawMasterVolume(const auto& index){
            posY = getPosY(index);
        
            DrawText(texts[4].c_str(), posX, posY, textSize, color);
            DrawText(TextFormat("%.0f%%", masterVolume * 100), posX + MeasureText(texts[4].c_str(), textSize) + offSet, posY, textSize, (masterVolume <= 0.4)? RED : (masterVolume <= 0.7)? YELLOW : GREEN);
            
        }
        void drawInputMode(const auto& index){
            posY = getPosY(index);

            DrawText(texts[5].c_str(), posX, posY, textSize, color);
            // (playerInputMode == WASD)? BLUE : (playerInputMode == ArrowKeys)? PURPLE : BEIGE);      
            DrawText(TextFormat("%s", (playerInputMode == WASD)? "WASD Keys" : (playerInputMode == ARROW)? "Arrow Keys" : "Mouse Wheel"), posX + MeasureText(texts[5].c_str(), textSize) + offSet, posY, textSize, BEIGE);  
        }

    public:
        Settings(GameState& gameState) : State(gameState) {
            settingModifySFX = LoadSound("../../../assets/sounds/sfx/settingModify.mp3");
        }
        ~Settings(){
            UnloadSound(settingModifySFX);
        }

        void draw(){
            // header
            drawHeader(1);

            // fullScreen
            drawFullScreen(2);

            // grid toggle
            drawGrid(3);

            // frame rate
            drawFrameRate(4);

            // window opacity
            drawWindowOpacity(5);

            // master volume
            drawMasterVolume(6);

            // input mode
            drawInputMode(7);

            // instructions
            // DrawText("Click on a setting or scroll through it to change it.", GetScreenWidth() - MeasureText("Click on a setting or scroll through it to change it.", 23), 35, 23, GOLD);
            DrawText("Press ENTER to go back.", GetScreenWidth() - MeasureText("Press ENTER to go back.", 23) - 23, GetScreenHeight() - 50, 23, GOLD);
        }

        void update(){
            if (IsKeyPressed(KEY_ENTER)){
                gameState = MENU;
            }

            posY = getPosY(1);

            // enableFullScreen
            posY = getPosY(2);
            // if (CheckCollisionPointRec(GetMousePosition(), Rectangle{(float) posX + MeasureText(texts[0].c_str(), textSize) + offSet, (float) posY, (float) MeasureText("Disabled", textSize), (float) textSize}) && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || GetMouseWheelMove()))
            // {
            //     enableFullScreen = !enableFullScreen;
            //     if (enableFullScreen){
            //         // SetWindowState(FLAG_enableFullScreen_MODE);
            //         SetWindowState(FLAG_BORDERLESS_WINDOWED_MODE); // op :D
            //     }
            //     else{
            //         ClearWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
            //         SetWindowSize(1080, 720);
            //     }

            //     PlaySound(settingModifySFX);
            // }

            // grid toggle
            posY = getPosY(3);
            if (CheckCollisionPointRec(GetMousePosition(), Rectangle{(float) posX + MeasureText(texts[1].c_str(), textSize) + offSet, (float) posY, (float) MeasureText("Disabled", textSize), (float) textSize}) && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || GetMouseWheelMove()))
            {
                enableGrid = !enableGrid;
                PlaySound(settingModifySFX);
            }

            // framerate
            posY = getPosY(4);
            if (CheckCollisionPointRec(GetMousePosition(), Rectangle{(float) posX + MeasureText(texts[2].c_str(), textSize) + offSet, (float) posY, (float) MeasureText("123", textSize), (float) textSize}) && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || GetMouseWheelMove()))          // 123 is the max width of poss values
            {

                switch (frameRate) {
                    case 15: frameRate = 30; break;
                    case 30: frameRate = 45; break;
                    case 45: frameRate = 60; break;
                    case 60: frameRate = 15; break;
                    default: frameRate = 60; break;
                }

                // what is this code...
                // dear God
                // frameRate = ((frameRate == 20)? 40 : (frameRate == 40)? 60 : (frameRate == 60)? 120 : 20);          // y these values? simple: me like em :)
                
                SetTargetFPS(frameRate);
                PlaySound(settingModifySFX);
            }

            // window opacity
            posY = getPosY(5);
            if (CheckCollisionPointRec(GetMousePosition(), Rectangle{(float) posX + MeasureText(texts[3].c_str(), textSize) + offSet, (float) posY, (float) MeasureText("0.1", textSize), (float) textSize}) && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || GetMouseWheelMove()))          // 0.1 is the max width of poss values
            {
                windowOpacity += 0.1f;
                if (windowOpacity >= 1.1f){             // >= needed since float addition can result in smthing like 1.00001f (wahi fpn kay precision ka masla)
                    windowOpacity = 0.1f;
                }
                
                SetWindowOpacity(windowOpacity);
                PlaySound(settingModifySFX);
            }

            // master volume
            posY = getPosY(6);
            if (CheckCollisionPointRec(GetMousePosition(), Rectangle{(float) posX + MeasureText(texts[4].c_str(), textSize) + offSet, (float) posY, (float) MeasureText("100%", textSize), (float) textSize}) && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || GetMouseWheelMove()))          // 100% is the max width of poss values
            {
                masterVolume += 0.1f;
                if (masterVolume >= 1.1f){             // >= needed since float addition can result in smthing like 1.00001f (wahi fpn kay precision ka masla)
                    masterVolume = 0.0f;
                }
                
                SetMasterVolume(masterVolume);
                PlaySound(settingModifySFX);             // to test modified vol
            }

            // input mode
            posY = getPosY(7);
            if (CheckCollisionPointRec(GetMousePosition(), Rectangle{(float) posX + MeasureText(texts[5].c_str(), textSize) + offSet, (float) posY, (float) MeasureText("Mouse Wheel", textSize), (float) textSize}) && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || GetMouseWheelMove()))          // "Mouse Wheel" is the max width of poss values
            {
                playerInputMode = ((playerInputMode == WASD)? ARROW : (playerInputMode == ARROW)? MOUSE : WASD);
                
                PlaySound(settingModifySFX);
            }
        }
        InputMode& getMovementMode(){
            return playerInputMode;
        }
        bool isFullScreenEnabled(){
            return enableFullScreen;
        }
        bool isGridEnabled(){
            return enableGrid;
        }
};