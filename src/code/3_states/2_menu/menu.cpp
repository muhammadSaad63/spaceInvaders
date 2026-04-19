#include "menu.hpp"
#include "../../2_entities/lasers/lasers.hpp"


MenuIcons::MenuIcons() : selected(false), selectedDelay(1.5) 
{
    icons[0] = MenuIcon{Rectangle{390, 50,  300, 120}, "Play",         75, PLAYING     };      // Play
    icons[1] = MenuIcon{Rectangle{180, 180, 200, 80 }, "LeaderBoards", 25, LEADERBOARDS};      // LeaderBoards
    icons[2] = MenuIcon{Rectangle{700, 180, 200, 80 }, "Shop",         25, SHOP        };      // Shop
    icons[3] = MenuIcon{Rectangle{50,  280, 150, 60 }, "History",      20, HISTORY     };      // History
    icons[4] = MenuIcon{Rectangle{880, 280, 150, 60 }, "Settings",     20, SETTINGS    };      // Settings
};
void MenuIcons::draw(){
    for (const auto& icon : icons){
        DrawRectangleGradientH(icon.rect.x, icon.rect.y, icon.rect.width, icon.rect.height, GOLD, RED);
        
        // a light black rectangular overlay over button
        DrawRectangle(icon.rect.x, icon.rect.y, icon.rect.width, icon.rect.height, ColorAlpha(BLACK, 0.1f));
        
        // centre text inside rect
        int   textWidth = MeasureText(icon.text.c_str(), icon.textSize);
        float textX     = icon.rect.x + (icon.rect.width  - textWidth) / 2;
        float textY     = icon.rect.y + (icon.rect.height - icon.textSize ) / 2;
        DrawText(icon.text.c_str(), textX, textY, icon.textSize, WHITE);
        
        if (selected && (icon.gameState == selectedState)) 
        DrawRectangleRoundedLinesEx(icon.rect, 0.1f, 10, 5, RAYWHITE);
    }
}
GameState MenuIcons::update(SpaceShip& spaceShip){
    vector<Laser>& lasers = spaceShip.getLasers();

    // if an icon was previously successfuly selected
    if (selected){
        if ((selectedTime + selectedDelay) <= GetTime()){
            spaceShip.reset();
            selected = false;

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