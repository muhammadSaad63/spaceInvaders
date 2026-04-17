#include <raylib.h>




#include <array>
#include <raylib.h>
#include <string>
using std::array, std::string;


class Alien{
    private:
        Texture2D alien;
        bool      active;

        void loadAlien(const string& fileName){
            alien = LoadTexture(fileName.c_str());
        }

    public:
        Alien() : active(true)
        { alien = LoadTexture("1.png"); }

        bool isActive(){
            return active;
        }
        Texture2D& getTexture(){
            return alien;
        }
};

enum Direction{
    LEFT,
    RIGHT,
    DOWN
};

class Aliens{
    private:
        const static int                          numRows     {3};
        const static int                          numAliens {7};                        // dunno u but was not working without static
        array<array<Alien, numAliens>, numRows> aliens;                                 // 2D array of Alien
        const float                               scale       {0.1f};
        // Direction                                 direction   {RIGHT};
        
        const int edgePadding { 63 };                                                      // on one side
        // const int alienWidth  { (GetScreenWidth() - (padding_X * 2)) / numAliens };
        const int alienWidth  { (aliens[0][0].getTexture().width  * scale) + 13 };
        const int rowWidth    { (aliens[0][0].getTexture().height * scale) + 13 };

        Vector2 swarmPos {0, 63};
        int speed {2.0};
        int direction;              // 1 right, -1 left
        const int swarmWidth { (alienWidth * (numAliens - 1)) + (aliens[0][0].getTexture().width) };

        bool hittingLeftEdge(){
            return (swarmPos.x <= edgePadding);
        }
        bool hittingRightEdge(){
            return ((swarmPos.x + swarmWidth) >= (GetScreenWidth() - edgePadding));
        }


    public:
        void draw(){
            auto posy {45};

            for (auto& rowOfAlien : aliens){
                auto posx = (GetScreenWidth() - (numAliens * alienWidth))/2;
                // auto posx {alienWidth};
                posy += (rowWidth);

                for (auto& alien : rowOfAlien){
                    if (alien.isActive()){
                        DrawTextureEx(alien.getTexture(), Vector2{(float)posx, (float)posy}, 0.0f, 0.1f, WHITE);
                    }

                    posx += alienWidth;
                }   
            }
        }
        void update(){
            swarmPos.x += (speed * direction);

            if (hittingLeftEdge() || hittingRightEdge()){
                direction *= -1;

                swarmPos.y += rowWidth;
            }
        }

        bool areAllDestroyed(){
            for (auto& rowOfAlien : aliens){
                for (auto& alien : rowOfAlien){
                    if (alien.isActive()){
                        return false;
                    }
                }   
            }

            return true;
        }
};


int main(){
    InitWindow(1080, 720, "test");
    SetTargetFPS(60);

    Aliens a;

    while (!WindowShouldClose()){
        
        BeginDrawing();
            a.draw();  
        EndDrawing();  
    }

    CloseWindow();
}