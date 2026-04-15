#include "settings.hpp"


class Settings : public State{
    // copied from your Mr.Pong game

    private:
        bool         fullScreen      {false};         // setwindowstate(FLAG_BORDERLESS_WINDOWED_MODE); ClearWindowState(); SetWindowSize();
        bool         showGrid        {true};          // whether to show the background grid or not
        int          frameRate       {60};            // again, why 63.
        float        windowOpacity   {0.9f};
        float        masterVolume    {0.5};
        InputMode    playerInputMode {WASD};

        const int    posX            {23};
        int          posY            {63};
        const int    textSize        {35};
        const int    offSet          {100};             // gap between text/heading and option/toggler
        const Color  color           {GOLD};
        const string texts[6]        {"   > FullScreen     ", "   > Grid              ", "   > FrameRate     ", "   > Window Opacity", "   > SFX Volume    ", "   > Input Mode    "};

        Sound settingModifySFX;

    public:
        Settings(GameState& gameState) : State(gameState) 
        {
            settingModifySFX = LoadSound("../assets/sounds/sfx/settingModify.mp3");
        }
        ~Settings(){
            UnloadSound(settingModifySFX);
        }

        void draw(){
            posY = 23;

            // header
            DrawText("Settings", posX, posY, 53, GOLD);

            // instructions
            // DrawText("Click on a setting or scroll through it to change it.", GetScreenWidth() - MeasureText("Click on a setting or scroll through it to change it.", 23), 35, 23, GOLD);
            DrawText("Press ENTER to go back.", GetScreenWidth() - MeasureText("Press ENTER to go back.", 23) - 23, GetScreenHeight() - 50, 23, GOLD);

            // fullscreen
            posY += (offSet + ((fullScreen)? 63 : 0));
            DrawText(texts[0].c_str(), posX, posY, textSize, color);
            DrawText(TextFormat("%s", (fullScreen)? "Enabled" : "Disabled"), posX + MeasureText(texts[0].c_str(), textSize) + 100, posY, textSize, (fullScreen)? GREEN : RED);

            // grid toggle
            posY += offSet;
            DrawText(texts[1].c_str(), posX, posY, textSize, color);
            DrawText(TextFormat("%s", (showGrid)? "Enabled" : "Disabled"), posX + MeasureText(texts[1].c_str(), textSize) + 100, posY, textSize, (showGrid)? GREEN : RED);

            // frame rate
            posY += offSet;
            DrawText(texts[2].c_str(), posX, posY, textSize, color);
            DrawText(TextFormat("%d", frameRate), posX + MeasureText(texts[2].c_str(), textSize) + 100, posY, textSize, (frameRate == 23)? RED : (frameRate == 40)? ORANGE : (frameRate == 63)? YELLOW : GREEN);
            
            // window opacity
            posY += offSet;
            DrawText(texts[3].c_str(), posX, posY, textSize, color);
            DrawText(TextFormat("%.1f", windowOpacity), posX + MeasureText(texts[3].c_str(), textSize) + offSet, posY, textSize, (windowOpacity <= 0.4)? RED : (windowOpacity <= 0.7)? YELLOW : GREEN);
            
            // master volume
            posY += offSet;
            DrawText(texts[4].c_str(), posX, posY, textSize, color);
            DrawText(TextFormat("%.0f%%", masterVolume * 100), posX + MeasureText(texts[4].c_str(), textSize) + offSet, posY, textSize, (masterVolume <= 0.4)? RED : (masterVolume <= 0.7)? YELLOW : GREEN);

            // input mode
            posY += offSet;
            DrawText(texts[5].c_str(), posX, posY, textSize, color);
            // (playerInputMode == WASD)? BLUE : (playerInputMode == ArrowKeys)? PURPLE : BEIGE);      
            DrawText(TextFormat("%s", (playerInputMode == WASD)? "WASD Keys" : (playerInputMode == ARROW)? "Arrow Keys" : "Mouse Wheel"), posX + MeasureText(texts[5].c_str(), textSize) + offSet, posY, textSize, BEIGE);  
        }

        void update(){
            if (IsKeyPressed(KEY_ENTER)){
                gameState = MENU;
            }

            posY = 23;

            // fullscreen
            posY += (offSet + ((fullScreen)? 63 : 0));
            // if (CheckCollisionPointRec(GetMousePosition(), Rectangle{(float) posX + MeasureText(texts[0].c_str(), textSize) + offSet, (float) posY, (float) MeasureText("Disabled", textSize), (float) textSize}) && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || GetMouseWheelMove()))
            // {
            //     fullScreen = !fullScreen;
            //     if (fullScreen){
            //         // SetWindowState(FLAG_FULLSCREEN_MODE);
            //         SetWindowState(FLAG_BORDERLESS_WINDOWED_MODE); // op :D
            //     }
            //     else{
            //         ClearWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
            //         SetWindowSize(1080, 720);
            //     }

            //     PlaySound(settingModifySFX);
            // }

            // grid toggle
            posY += offSet;
            if (CheckCollisionPointRec(GetMousePosition(), Rectangle{(float) posX + MeasureText(texts[1].c_str(), textSize) + offSet, (float) posY, (float) MeasureText("Disabled", textSize), (float) textSize}) && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || GetMouseWheelMove()))
            {
                showGrid = !showGrid;
                PlaySound(settingModifySFX);
            }

            // framerate
            posY += offSet;
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
            posY += offSet;
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
            posY += offSet;
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
            posY += offSet;
            if (CheckCollisionPointRec(GetMousePosition(), Rectangle{(float) posX + MeasureText(texts[5].c_str(), textSize) + offSet, (float) posY, (float) MeasureText("Mouse Wheel", textSize), (float) textSize}) && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || GetMouseWheelMove()))          // "Mouse Wheel" is the max width of poss values
            {
                playerInputMode = ((playerInputMode == WASD)? ARROW : (playerInputMode == ARROW)? MOUSE : WASD);
                
                PlaySound(settingModifySFX);
            }
        }
        InputMode& getMovementMode(){
            return playerInputMode;
        }
        bool isFullScreen(){
            return fullScreen;
        }
        bool isGridEnabled(){
            return showGrid;
        }
};