#include <cmath>
#include "menu.hpp"
#include "../../2_entities/lasers/lasers.hpp"
using std::fmodf;


MenuIcons::MenuIcons() : selected(false), selectedDelay(3) 
{
    icons[0] = MenuIcon{Rectangle{390, 50,  300, 120}, "Play",         75, PLAYING     };      // Play
    icons[1] = MenuIcon{Rectangle{180, 180, 200, 80 }, "Statistics",   25, STATISTICS  };      // LeaderBoards
    icons[2] = MenuIcon{Rectangle{700, 180, 200, 80 }, "Shop",         25, SHOP        };      // Shop
    icons[3] = MenuIcon{Rectangle{50,  280, 150, 60 }, "History",      20, HISTORY     };      // History
    icons[4] = MenuIcon{Rectangle{880, 280, 150, 60 }, "Settings",     20, SETTINGS    };      // Settings

    iconSelectedSFX = LoadSound("src/assets/sounds/sfx/iconSelected.mp3");
    stateChangedSFX = LoadSound("src/assets/sounds/sfx/stateChanged.mp3");
};
MenuIcons::~MenuIcons(){
    UnloadSound(iconSelectedSFX);
    UnloadSound(stateChangedSFX);
}
void MenuIcons::draw(){
    for (const auto& icon : icons){
        if (selected){                                              // if an icon is/was already selected
            auto timePassed = (GetTime() - selectedTime);
            auto alpha      = fmodf(timePassed, 1.0f);              // 3.0f / 0.6f -> 5x pulses
            auto inc        = 23;
    
            if (icon.gameState == selectedState){                   // if the curr icon is the selected one
                // DrawRectangleGradientH(icon.rect.x - inc*alpha, icon.rect.y-inc*alpha, icon.rect.width+2*inc*alpha, icon.rect.height+2*inc*alpha, GOLD, RED);
                // DrawRectangleGradientH(icon.rect.x, icon.rect.y, icon.rect.width, icon.rect.height, ColorAlpha(GOLD, alpha), ColorAlpha(RED, alpha));
                // DrawRectangleGradientH(icon.rect.x - (inc * alpha), icon.rect.y - (inc * alpha), icon.rect.width + (2 * inc * alpha), icon.rect.height + (2 * inc * alpha), ColorAlpha(GOLD, alpha), ColorAlpha(RED, alpha));
                DrawRectangleGradientH(icon.rect.x, icon.rect.y, icon.rect.width, icon.rect.height, ColorAlpha(GOLD, alpha), ColorAlpha(RED, alpha));
            }
            else{
                // DrawRectangleGradientH(icon.rect.x + (inc * alpha), icon.rect.y + (inc * alpha), icon.rect.width - (2 * inc * alpha), icon.rect.height - (2 * inc * alpha), GOLD, RED);
                // DrawRectangleGradientH(icon.rect.x, icon.rect.y, icon.rect.width, icon.rect.height, ColorAlpha(GOLD, alpha), ColorAlpha(RED, alpha));
                // DrawRectangleGradientH(icon.rect.x + inc/2, icon.rect.y + inc/2, icon.rect.width - inc, icon.rect.height - inc, GOLD, RED);
                DrawRectangleGradientH(icon.rect.x, icon.rect.y, icon.rect.width, icon.rect.height, GOLD, RED);
            }
        }
        else{                                                   // no icon was previously selected
            DrawRectangleGradientH(icon.rect.x, icon.rect.y, icon.rect.width, icon.rect.height, GOLD, RED);
        }
        
        // centre text inside rect
        int   textWidth = MeasureText(icon.text.c_str(), icon.textSize);
        float textX     = icon.rect.x + (icon.rect.width  - textWidth) / 2;
        float textY     = icon.rect.y + (icon.rect.height - icon.textSize ) / 2;
        DrawText(icon.text.c_str(), textX, textY, icon.textSize, RAYWHITE);
    }
}
GameState MenuIcons::update(SpaceShip& spaceShip){
    vector<Laser>& lasers = spaceShip.getLasers();

    // if an icon was previously successfuly selected
    if (selected){
        if (GetTime() >= (selectedTime + selectedDelay)){
            spaceShip.reset();
            selected = false;
            PlaySound(stateChangedSFX);

            return selectedState;
        }
    }

    // checking for any successful selections/collisions
    for (auto& icon : icons){
        for (auto& laser : lasers){
            if (CheckCollisionRecs(icon.rect, laser.getRect())){
                laser.deActivate();
                
                if (!selected){
                    selected      = true;
                    selectedTime  = GetTime();
                    selectedState = icon.gameState;

                    PlaySound(iconSelectedSFX);
                }
            }
        }
    }

    return MENU;
}

Menu::Menu(GameState& gameState, Settings& settings) 
    : State(gameState)
    , spaceShip("1.png")
    , movementMode(settings.getMovementMode())
    {}

void Menu::draw(){
    spaceShip.draw();
    icons.draw();
}
void Menu::update(){
    spaceShip.update(movementMode);
    gameState = icons.update(spaceShip);
}