#pragma once


#include <string>
#include "../1_state/state.hpp"
#include "../../1_core/enums/gameState.hpp"
#include "../../1_core/enums/inputMode.hpp"
using std::string;


class Settings : public State{
    // copied from your Mr.Pong game - ebbi

    private:
        bool         enableFullScreen {false};         // setwindowstate(FLAG_BORDERLESS_WINDOWED_MODE); ClearWindowState(); SetWindowSize();
        bool         enableGrid       {true};          // whether to show the background grid or not
        int          frameRate        {60};            // again, why 63.
        float        windowOpacity    {0.9f};
        float        masterVolume     {0.5};
        InputMode    playerInputMode  {WASD};

        const int    posX             {23};
        const int    initPosY         {23};            // the y value at which to start drawing
        int          posY             {};
        const int    textSize         {35};
        const int    offSet           {100};           // gap between text/heading and option/toggler
        const Color  color            {GOLD};
        const string texts[6]         {"   > FullScreen     ", "   > Grid              ", "   > FrameRate     ", "   > Window Opacity", "   > SFX Volume    ", "   > Input Mode    "};

        Sound settingModifiedSFX;

        // internal, helper functions
        int getPosY(const int& index);

        // draw helpers
        void drawHeader(const int& index);
        void drawFullScreen(const int& index);
        void drawGrid(const int& index);
        void drawFrameRate(const int& index);
        void drawWindowOpacity(const int& index);
        void drawMasterVolume(const int& index);
        void drawInputMode(const int& index);

        // update helpers
        void updateFullScreen(const int& index);
        void updateGrid(const int& index);
        void updateFrameRate(const int& index);
        void updateWindowOpacity(const int& index);
        void updateMasterVolume(const int& index);
        void updateInputMode(const int& index);

    public:
        Settings(GameState& gameState);
        ~Settings();

        void draw();
        void update();

        InputMode& getMovementMode();
        bool isFullScreenEnabled();
        bool isGridEnabled();
};