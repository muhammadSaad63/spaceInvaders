#include <array>
#include <string>
#include <vector>
#include <raylib.h>
using std::array, std::string, std::vector;


class Alien{
    private:
        Texture2D texture;
        bool      active;

        void loadAlien(const string& fileName){
            texture = LoadTexture(fileName.c_str());
        }

    public:
        Alien() : active(true)
        { texture = LoadTexture("1.png"); }

        void draw(const Vector2& position, const int& scale){
            DrawTextureEx(texture, position, 0.0f, scale, WHITE);
        }
        bool isActive(){
            return active;
        }
        Texture2D& getTexture(){
            return texture;
        }   
        void activate(){
            if (!active)
            { active = true; }
        }
        void deActivate(){
            if (active)
            { active = false; }
        }
};

class Aliens{
    private:
        const static int                        numRows   {3};
        const static int                        numAliens {5};                                                   // dunno u but was not working without static
        array<array<Alien, numAliens>, numRows> aliens;                                                          // 2D array of Alien
        const float                             scale     {0.1f};
        
        const int edgePadding { 63 };                                                                            // on one side
        // const int alienSpacing  { (GetScreenWidth() - (padding_X * 2)) / numAliens };
        // const int alienSpacing  { (aliens[0][0].getTexture().width  * scale) + 13 };
        const int alienSpacing  { 81 };
        // const int rowSpacing    { (aliens[0][0].getTexture().height * scale) + 13 };
        const int rowSpacing    { 70 };

        Vector2 swarmPos {};
        float speed {1.0f};
        int direction {-1};                                                                                     // 1 right, -1 left
        // const int swarmWidth { (alienSpacing * (numAliens - 1)) + (aliens[0][0].getTexture().width) };
        const int swarmWidth { (alienSpacing * (numAliens - 1)) + (alienSpacing) };

        // vector<Laser> lasers;

        bool hittingLeftEdge(){
            return (swarmPos.x <= edgePadding);
        }
        bool hittingRightEdge(){
            return ((swarmPos.x + swarmWidth) >= (GetScreenWidth() - edgePadding));
        }
        Rectangle getAlienRect(const int& rowNum, const int& alienNum){
            return Rectangle{
                    (swarmPos.x + ((alienNum - 1) * alienSpacing)),
                    (swarmPos.y + ((alienNum - 1) * rowSpacing)),
                    (float) (aliens[rowNum][alienNum].getTexture().width),
                    (float) (aliens[rowNum][alienNum].getTexture().height)
            };
        }
        void centerSwarm(){
            swarmPos.x = ((GetScreenWidth() - swarmWidth) / 2);
            swarmPos.y = 63;
        }


    public:
        Aliens(){
            centerSwarm();                                                                           // centering swarm at start
        }

        void draw(){
            Vector2 position {};

            for (auto rowNum {0}; rowNum < numRows; ++rowNum){
                for (auto alienNum {0}; alienNum < numAliens; ++alienNum){
                    position.x = (swarmPos.x + (alienSpacing * alienNum));
                    position.y = (swarmPos.y + (rowNum * rowSpacing));

                    aliens[rowNum][alienNum].draw(position, scale);
                }
            }
        }
        void update(){
            swarmPos.x += (speed * direction);

            if (hittingLeftEdge() || hittingRightEdge()){
                direction *= -1;

                swarmPos.y += (rowSpacing / 3);
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
        void reset(){
            centerSwarm();

            for (auto& rowOfAliens : aliens){
                for (auto& alien : rowOfAliens){
                    alien.activate();
                }
            }
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