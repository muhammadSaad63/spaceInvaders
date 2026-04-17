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
        const string texts[6]         {"   > enableFullScreen     ", "   > Grid              ", "   > FrameRate     ", "   > Window Opacity", "   > SFX Volume    ", "   > Input Mode    "};

        Sound settingModifySFX;

        // internal, helper functions
        int getPosY(const auto& index);

        // draw helpers
        void drawHeader(const auto& index);
        void drawFullScreen(const auto& index);
        void drawGrid(const auto& index);
        void drawFrameRate(const auto& index);
        void drawWindowOpacity(const auto& index);
        void drawMasterVolume(const auto& index);
        void drawInputMode(const auto& index);

        // update helpers
        void updateFullScreen(const auto& index);
        void updateGrid(const auto& index);
        void updateFrameRate(const auto& index);
        void updateWindowOpacity(const auto& index);
        void updateMasterVolume(const auto& index);
        void updateInputMode(const auto& index);

    public:
        Settings(GameState& gameState);
        ~Settings();

        void draw();
        void update();

        InputMode& getMovementMode();
        bool isFullScreenEnabled();
        bool isGridEnabled();
};