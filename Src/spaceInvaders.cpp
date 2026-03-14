//                                                             بسم اللہ الرحمان الرحیم  

#include <string>
#include <vector>
#include <iostream>
#include <raylib.h>
using std::cout, std::string, std::vector;

/*
    [Started]
        > Mar 9th, 2026

    [Abstract]
        >

    TODO
        - implement alien, aliens, & playing
        - collisions
        - 

    [Finished]
        >
*/

// Enums -----

enum GameState{                 // an ENUM to indicate the current state of the game
    // mainMenu
        MENU,                   // the mainMenu screen of the game; contains the following 👇
            PLAY,               // contains options such as playerName, difficulty, spaceShip skin etc
            SHOP,               // buy diff spaceShip skins, aliens' skins, SFX perhaps
            HISTORY,            // show gameHistory (using sqlite)
            LEADERBOARDS,       // display leaderBoards with top10 players (using sqlite)
            SETTINGS,           // game settings such as fullscreen, SFX volume, playerInputMode, opacity etc (similar to Mr. Pong's)

    // gamePlay
        PLAYING,                // actual gamePlay state
        PAUSED,                 // while game is paused inside PLAYING
        GAMEOVER,               // when game ends inside PLAYING; shows outcome, score, aliens-defeated, coins earned etc

    // windowShouldClose()
        CLOSEGAME               // when user chooses to close the window; plays a meme or similar
};
enum Player{
    USER,                       // used to refer to the user/player/human
    ALIEN                       // used to refer to the enemy/computer/pc/alien(s)
};
enum InputMode{                 // an ENUM to indicate the chosen playerInputMode (altered in settings)
    WASD,                       // W & A keys
    ARROW,                      // left & right arrowKeys
    MOUSE                       // Left & Right mouseButtons
};


// Classes -----

class State{                                                        // an abstract class to be inherited by all gameState subclasses
    protected:
        GameState& gameState;

    public:
        State(GameState& gameState) : gameState(gameState) {}

        virtual void draw()   = 0;

        virtual void update() = 0;
};
class Menu : public State{
    private:
        //

    public:
        Menu(GameState& gameState) : State(gameState) {}

        void draw(){

        }
        void update(){

        }
};
class Play : public State{
    private:
        //

    public:
        Play(GameState& gameState) : State(gameState) {}

        void draw(){

        }
        void update(){

        }
};
class Shop : public State{
    private:
        //

    public:
        Shop(GameState& gameState) : State(gameState) {}

        void draw(){

        }
        void update(){

        }
};
class History : public State{
    private:
        //

    public:
        History(GameState& gameState) : State(gameState) {}

        void draw(){

        }
        void update(){

        }
};
class LeaderBoards : public State{
    private:
        //

    public:
        LeaderBoards(GameState& gameState) : State(gameState) {}

        void draw(){

        }
        void update(){

        }
};
class Settings : public State{
    private:
        //
        InputMode movementMode;

    public:
        Settings(GameState& gameState)
        : State(gameState)
        , movementMode(WASD) 
        {}

        void draw(){

        }
        void update(){

        }
        InputMode& getMovementMode(){
            return movementMode;
        }
};

class Laser{
    private:
        float posX;
        float posY;
        float width;
        float height;

        int speed;
        bool active;
        
    public:
        Laser(int posX, int posY){
            this->posX = posX;
            this->posY = posY;

            width = 5;
            height = 25;
            speed = 9;
            active = true;
        }
        void update(Player playerType){
            switch (playerType)
            {
                case USER:                                         
                    posY -= speed;                                  // if the user fired the laser, decrease its posX by speed (ie move it up)
                    if (posY <= 0){
                        deActivate();
                        cout << "[GAME] Laser deactivated!\n";
                    }
                    break;     
                case ALIEN: 
                    posY += speed;                                  // if the aliens fired the laser, increase its posX by speed (ie move it down)
                    if ((posY + height) >= GetScreenHeight()){
                        deActivate();
                    }
                    break;    
            }
        }
        void draw(){    
            DrawRectangle(posX, posY, width, height, WHITE);
        }
        Rectangle getRect(){
            return Rectangle{posX, posY, width, height};
        }
        bool isActive(){
            return active;
        }
        void deActivate(){
            active = false;
        }
};
class SpaceShip{
    private:
        Texture spaceShip;
        float posX;
        float posY;
        float scale;            // the scale by which to shrink the spaceShip texture; default 0.1f
        int bottomOffset;       // the value by which to offset/raise the ship from the bottom of the screen; default 50
        float speed;

        vector<Laser> lasers;
        
        void loadShip(const string& fileName){
            spaceShip = LoadTexture(TextFormat("Assets/Sprites/spaceShips/%s", fileName.c_str()));
            
            // returns true if the texture is loaded into memory; alternatively coudlve used "if (spaceShip.id)"
            cout << "[GAME] SpaceShip texture (" << fileName << (IsTextureValid(spaceShip)? ") has" : ") has NOT") << " loaded properly.\n";
        }

    public:
        SpaceShip(const string& fileName){
            loadShip(fileName);

            scale = 0.1f;
            bottomOffset = 50;

            posX = (GetScreenWidth() / 2 - (spaceShip.width * scale) / 2);
            posY = (GetScreenHeight() - (spaceShip.height * scale) - bottomOffset); 

            speed = 5;
        }
        ~SpaceShip(){
            UnloadTexture(spaceShip);
        }

        void draw(){
            // DrawTexture(spaceShip, posX, posY, WHITE);                                     // doesnt allow scaling
            DrawTextureEx(spaceShip, Vector2{(float) posX, (float) posY}, 0.0f, 0.1f, WHITE);

            for (auto &laser : lasers){
                if (laser.isActive()){
                    laser.draw(); 
                }
            }
        }
        void update(InputMode inputMode){
            int screenWidth = GetScreenWidth();

            // moving ship
            switch (inputMode)
            {
                case WASD:
                {
                    if (IsKeyDown(KEY_A)){
                        posX -= speed;

                        if (posX <= 0)
                        { posX = 0; }
                    }
                    if (IsKeyDown(KEY_D)){
                        posX += speed;

                        if ((posX + (spaceShip.width * scale)) >= screenWidth)
                        { posX = screenWidth - (spaceShip.width * scale); }
                    }

                    break;
                }
                case ARROW:
                {
                    if (IsKeyDown(KEY_LEFT)){
                        posX -= speed;

                        if (posX <= 0)
                        { posX = 0; }
                    }
                    if (IsKeyDown(KEY_RIGHT)){
                        posX += speed;

                        if ((posX + (spaceShip.width * scale)) >= screenWidth)
                        { posX = screenWidth - (spaceShip.width * scale); }
                    }

                    break;
                }
                case MOUSE:
                {
                    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                        posX -= speed;

                        if (posX <= 0)
                        { posX = 0; }
                    }
                    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
                        posX += speed;

                        if ((posX + (spaceShip.width * scale)) >= screenWidth)
                        { posX = screenWidth - (spaceShip.width * scale); }
                    }

                    break;
                }
            }

            // firing lasers
            if (IsKeyPressed(KEY_SPACE)){
                lasers.push_back(Laser{(int) (posX + (spaceShip.width * scale)/2), (int) posY});
            }

            // updating lasers
            // for (auto &laser : lasers){
            //     if (laser.isActive()){
            //         laser.update(USER);
            //     }
            //     else{
            //         lasers.erase(laser);
            //     }
            // }

            for (auto it = lasers.begin(); it != lasers.end();){              // it = iterator; its similar to ptrs
                if (it->isActive()){                                          // updating laser if they active
                    it->update(USER);
                    ++it;
                }
                else{                                                         // removing laser if they inactive
                    it = lasers.erase(it);                                    // erase returns iterator to next element
                }
            }
        }
        void reset(){
            posX = (GetScreenWidth() / 2 - (spaceShip.width * scale) / 2);
            posY = (GetScreenHeight() - (spaceShip.height * scale) - bottomOffset); 
        }
        vector<Laser> getLasers(){
            return lasers;
        }
};


class Alien{
    private:
        int posX;
        int posY;
        int row;
        int col;
        int active;
        Texture alien;
        float scale;

    public:
        Alien() : active(true) {}

        void draw(){
            if (active){
                // DrawTexture(texture, posX,);

            }
        }
        void update(){
            // 
        }
};
class Aliens{
    private:
        vector<vector<Alien>> aliens;               // 2D array of Alien

    public:
        //
        void draw(){
            for (auto& rowOfAliens : aliens){
                for (auto& alien : rowOfAliens){
                    alien.draw();
                }
            }
        }
        void update(){
            for (auto& rowOfAliens : aliens){
                for (auto& alien : rowOfAliens){
                    alien.update();
                }
            }
        }
};

class MotherShip{
    private:
        Texture motherShip;
        int     lastSpawned;
        int     spawnDuration;
        int     currentlySpawned;
        int     hits;
        int     maxPossibleHits;
        int     scoreBoost;
        Vector2 position;           // using instead of posX, posY
        float   scale;
        int     randomSpawnPause;   // duration after which to spawn the mothership


    public:
        MotherShip() 
        : lastSpawned(GetTime())                                        // time when the ship last spawned; initialized with the getTime()
        , spawnDuration(15)                                             // will appear for a duration of 15s
        , currentlySpawned(false)                                       // is the motherShip currently spawned            
        , hits(0)                                                       // number of hits currently sustained by the motherShip
        , maxPossibleHits(5)                                            // max number of hits to defeat/destruct the motherShip
        , scoreBoost(1000)                                              // 1000 extra points on destruction
        , motherShip(LoadTexture("Assets/Sprites/motherShip/1.png"))
        , position({0.0f, 100})
        , scale(0.3f)
        , randomSpawnPause(30)                                          // 30s
        {}

        void draw(){
            if (currentlySpawned){
                DrawTextureEx(motherShip, position, 0.0f, scale, WHITE);
            }
        }
        void update(vector<Laser>& lasers){
            if (currentlySpawned){
                if (GetTime() >= (lastSpawned + spawnDuration)){            // despawning if it has spawned for >= spawnDuration time
                    currentlySpawned = false;
                    randomSpawnPause = GetRandomValue(20, 40);              // will spawn after a random n seconds (n > 20, < 40)
                    // playsound...
                    return;
                }
                for (auto& laser : lasers){
                    if (CheckCollisionRecs(laser.getRect(), motherShipRect())){
                        laser.deActivate();
                        hits++;
                    }
                }
                if (hits >= maxPossibleHits){
                    currentlySpawned = false;
                    randomSpawnPause = GetRandomValue(20, 40);              // will spawn after a random n seconds (n > 20, < 40)
                    // playsound
                }
            }
            else{
                if (GetTime() >= (lastSpawned + spawnDuration + randomSpawnPause)){            // despawning if it has spawned for >= spawnDuration time
                    currentlySpawned = true;
                    hits = 0;
                    lastSpawned = GetTime(); 
                    // playsound...
                }
            }
        }
        Rectangle motherShipRect(){
            return Rectangle{position.x, position.y, (float)(motherShip.width * scale), (float)(motherShip.height * scale)};
        }
};

class Playing : public State{
    private:
        SpaceShip  spaceShip; 
        Aliens     aliens;
        MotherShip motherShip;

        InputMode& movementMode;

    public:
        Playing(GameState& gameState, InputMode& movementMode) 
        : State(gameState)
        , spaceShip("1.png") 
        , movementMode(movementMode)
        {}

        void init(){

        }
        void draw(){
            spaceShip.draw();
            aliens.draw();
            motherShip.draw();
            // obstacles.draw();
        }
        void update(){
            spaceShip.update(movementMode);
            aliens.update();
            motherShip.update(spaceShip.)
            // obstacles.update();
        }
};



class Paused : public State{
    private:
        //

    public:
        Paused(GameState& gameState) : State(gameState) {}

        void draw(){

        }
        void update(){

        }
};
class GameOver : public State{
    private:
        //

    public:
        GameOver(GameState& gameState) : State(gameState) {}

        void draw(){

        }
        void update(){

        }
};
class CloseGame : public State{
    private:
        //

    public:
        CloseGame(GameState& gameState) : State(gameState) {}

        void draw(){

        }
        void update(){

        }
};
class Game{
    private:
        GameState gameState;

        Menu         menu;
        Play         play;
        Shop         shop;
        History      history;
        LeaderBoards leaderBoards;
        Settings     settings;

        Playing      playing;
        Paused       paused;
        GameOver     gameOver;

        CloseGame    closeGame;


    public:
        Game()                          // overRiding default constructor 
        : gameState(PLAYING)               // initializing gameState with MENU
        , menu(gameState)
        , play(gameState)
        , shop(gameState) 
        , history(gameState)
        , leaderBoards(gameState)
        , settings(gameState)
        , playing(gameState, settings.getMovementMode())
        , paused(gameState)
        , gameOver(gameState)
        , closeGame(gameState) 
        {}


        void draw(){                                                    // draws based upon the current gameState
            ClearBackground(BLANK);

            switch(gameState)
            {
                case MENU:         { menu.draw();         break; }
                case PLAY:         { play.draw();         break; }
                case SHOP:         { shop.draw();         break; }
                case HISTORY:      { history.draw();      break; }
                case LEADERBOARDS: { leaderBoards.draw(); break; }
                case SETTINGS:     { settings.draw();     break; }
                case PLAYING:      { playing.draw();      break; }
                case PAUSED:       { paused.draw();       break; }
                case GAMEOVER:     { gameOver.draw();     break; }
                case CLOSEGAME:    { closeGame.draw();    break; }  
            }
        }
        void update(){                                                  // updates based upon the current gameState
            switch(gameState)
            {
                case MENU:         { menu.update();         break; }
                case PLAY:         { play.update();         break; }
                case SHOP:         { shop.update();         break; }
                case HISTORY:      { history.update();      break; }
                case LEADERBOARDS: { leaderBoards.update(); break; }
                case SETTINGS:     { settings.update();     break; }
                case PLAYING:      { playing.update();      break; }
                case PAUSED:       { paused.update();       break; }
                case GAMEOVER:     { gameOver.update();     break; }
                case CLOSEGAME:    { closeGame.update();    break; }  
            }
        }
};


// Main ---

int main()
{
    InitWindow(1080, 720, "Space Invaders 👾");
    SetWindowOpacity(0.9);
    SetExitKey(KEY_ESCAPE);
    SetTargetFPS(63);

    Image favicon = LoadImage("Assets/Favicon/2.png");
    if (favicon.data){
        SetWindowIcon(favicon);
        UnloadImage(favicon);
    }

    Game game;

    while (!WindowShouldClose()){
        // updating
        game.update();

        // drawing
        BeginDrawing();

            game.draw();

        EndDrawing();
    }

    CloseWindow();
}