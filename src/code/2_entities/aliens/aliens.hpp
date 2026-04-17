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

class Aliens{
    private:
        const static int                          numRows     {3};
        const static int                          numAliens {5};                        // dunno u but was not working without static
        array<array<Alien, numAliens>, numRows> aliens;                                 // 2D array of Alien
        const float                               scale       {0.1f};
        
        const int edgePadding { 63 };                                                      // on one side
        // const int alienWidth  { (GetScreenWidth() - (padding_X * 2)) / numAliens };
        // const int alienWidth  { (aliens[0][0].getTexture().width  * scale) + 13 };
        const int alienWidth  { 81 };
        // const int rowWidth    { (aliens[0][0].getTexture().height * scale) + 13 };
        const int rowWidth    { 70 };

        Vector2 swarmPos {edgePadding + 23, 63};
        float speed {0.5f};
        int direction {-1};              // 1 right, -1 left
        // const int swarmWidth { (alienWidth * (numAliens - 1)) + (aliens[0][0].getTexture().width) };
        const int swarmWidth { (alienWidth * (numAliens - 1)) + (alienWidth) };

        bool hittingLeftEdge(){
            return (swarmPos.x <= edgePadding);
        }
        bool hittingRightEdge(){
            return ((swarmPos.x + swarmWidth) >= (GetScreenWidth() - edgePadding));
        }


    public:
        void draw(){
            Vector2 position {};

            for (auto rowOfAliens {0}; rowOfAliens < numRows; ++rowOfAliens){
                for (auto alien {0}; alien < numAliens; ++alien){
                    position.x = (swarmPos.x + (alienWidth * alien));
                    position.y = (swarmPos.y + (rowOfAliens * rowWidth));

                    DrawTextureEx(aliens[0][0].getTexture(), position, 0.0f, scale, WHITE);
                }
            }
        }
        void update(){
            swarmPos.x += (speed * direction);

            if (hittingLeftEdge() || hittingRightEdge()){
                direction *= -1;

                swarmPos.y += rowWidth/3;
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
        a.update();

        BeginDrawing();
            ClearBackground(BLANK);
            a.draw();  
        EndDrawing();  
    }

    CloseWindow();
}