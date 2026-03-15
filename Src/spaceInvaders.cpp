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
    // copied from my Mr.Pong game

    private:
        bool         fullScreen      {false};         // setwindowstate(FLAG_BORDERLESS_WINDOWED_MODE); ClearWindowState(); SetWindowSize();
        int          frameRate       {63};
        float        windowOpacity   {0.9f};
        float        masterVolume    {0.5};
        InputMode    playerInputMode {WASD};

        const int    posX            {23};
        int          posY            {63};
        const int    textSize        {35};
        const int    offSet          {100};             // gap between text/heading and option/toggler
        const Color  color           {GOLD};
        const string texts[5]        {"   > FullScreen     ", "   > FrameRate     ", "   > Window Opacity", "   > SFX Volume    ", "   > Input Mode    "};

        Sound settingModifySFX;

    public:
        Settings(GameState& gameState) : State(gameState) {
            settingModifySFX = LoadSound("Assets/SFX/settingModify.mp3");
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

            // frame rate
            posY += offSet;
            DrawText(texts[1].c_str(), posX, posY, textSize, color);
            DrawText(TextFormat("%d", frameRate), posX + MeasureText(texts[1].c_str(), textSize) + 100, posY, textSize, (frameRate == 23)? RED : (frameRate == 40)? ORANGE : (frameRate == 63)? YELLOW : GREEN);
            
            // window opacity
            posY += offSet;
            DrawText(texts[2].c_str(), posX, posY, textSize, color);
            DrawText(TextFormat("%.1f", windowOpacity), posX + MeasureText(texts[2].c_str(), textSize) + offSet, posY, textSize, (windowOpacity <= 0.4)? RED : (windowOpacity <= 0.7)? YELLOW : GREEN);
            
            // master volume
            posY += offSet;
            DrawText(texts[3].c_str(), posX, posY, textSize, color);
            DrawText(TextFormat("%.0f%%", masterVolume * 100), posX + MeasureText(texts[3].c_str(), textSize) + offSet, posY, textSize, (masterVolume <= 0.4)? RED : (masterVolume <= 0.7)? YELLOW : GREEN);

            // input mode
            posY += offSet;
            DrawText(texts[4].c_str(), posX, posY, textSize, color);
            // (playerInputMode == WASD)? BLUE : (playerInputMode == ArrowKeys)? PURPLE : BEIGE);      
            DrawText(TextFormat("%s", (playerInputMode == WASD)? "WASD Keys" : (playerInputMode == ARROW)? "Arrow Keys" : "Mouse Wheel"), posX + MeasureText(texts[4].c_str(), textSize) + offSet, posY, textSize, BEIGE);  
        }

        void update(){
            if (IsKeyPressed(KEY_ENTER)){
                gameState = MENU;
            }

            posY = 23;

            // fullscreen
            posY += (offSet + ((fullScreen)? 63 : 0));
            if (CheckCollisionPointRec(GetMousePosition(), Rectangle{(float) posX + MeasureText(texts[0].c_str(), textSize) + offSet, (float) posY, (float) MeasureText("Disabled", textSize), (float) textSize}) && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || GetMouseWheelMove()))
            {
                fullScreen = !fullScreen;
                if (fullScreen){
                    // SetWindowState(FLAG_FULLSCREEN_MODE);
                    SetWindowState(FLAG_BORDERLESS_WINDOWED_MODE); // op :D
                }
                else{
                    ClearWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
                    SetWindowSize(1300, 700);
                }

                PlaySound(settingModifySFX);
            }

            // framerate
            posY += offSet;
            if (CheckCollisionPointRec(GetMousePosition(), Rectangle{(float) posX + MeasureText(texts[1].c_str(), textSize) + offSet, (float) posY, (float) MeasureText("123", textSize), (float) textSize}) && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || GetMouseWheelMove()))          // 123 is the max width of poss values
            {
                frameRate = ((frameRate == 23)? 40 : (frameRate == 40)? 63 : (frameRate == 63)? 123 : 23);          // y these values? simple: me like em :)
                
                SetTargetFPS(frameRate);
                PlaySound(settingModifySFX);
            }

            // window opacity
            posY += offSet;
            if (CheckCollisionPointRec(GetMousePosition(), Rectangle{(float) posX + MeasureText(texts[2].c_str(), textSize) + offSet, (float) posY, (float) MeasureText("0.1", textSize), (float) textSize}) && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || GetMouseWheelMove()))          // 0.1 is the max width of poss values
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
            if (CheckCollisionPointRec(GetMousePosition(), Rectangle{(float) posX + MeasureText(texts[3].c_str(), textSize) + offSet, (float) posY, (float) MeasureText("100%", textSize), (float) textSize}) && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || GetMouseWheelMove()))          // 100% is the max width of poss values
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
            if (CheckCollisionPointRec(GetMousePosition(), Rectangle{(float) posX + MeasureText(texts[4].c_str(), textSize) + offSet, (float) posY, (float) MeasureText("Mouse Wheel", textSize), (float) textSize}) && (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || GetMouseWheelMove()))          // "Mouse Wheel" is the max width of poss values
            {
                playerInputMode = ((playerInputMode == WASD)? ARROW : (playerInputMode == ARROW)? MOUSE : WASD);
                
                PlaySound(settingModifySFX);
            }
        }
        InputMode& getMovementMode(){
            return playerInputMode;
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
                        // cout << "[GAME] Laser deactivated!\n";
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
        vector<Laser>& getLasers(){
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
        bool    currentlySpawned;
        int     hits;
        int     maxPossibleHits;
        int     scoreBoost;
        Vector2 position;           // using instead of posX, posY
        int     speed;              // speed by which to update position.x
        float   scale;
        int     randomSpawnPause;   // duration after which to spawn the mothership
        bool    spawnFromLeft;      // will be randomly decided;


    public:
        MotherShip() 
        : lastSpawned(0)                                                // time when the ship last spawned; initialized with the 0/getTime()
        , spawnDuration(15)                                             // will appear for a duration of 15s
        , currentlySpawned(false)                                       // is the motherShip currently spawned            
        , hits(0)                                                       // number of hits currently sustained by the motherShip
        , maxPossibleHits(7)                                            // max number of hits to defeat/destruct the motherShip
        , scoreBoost(1000)                                              // 1000 extra points on destruction
        , motherShip(LoadTexture("Assets/Sprites/motherShips/1.png"))
        , position({0.0f, 50})
        , scale(0.15f)
        , randomSpawnPause(30)                                          // 30s
        , speed(2)
        , spawnFromLeft(true)
        {}
        ~MotherShip(){
            if (IsTextureValid(motherShip))                             // this check is redundant tho...
            { UnloadTexture(motherShip);  }
        }
        void draw(){
            if (currentlySpawned){
                DrawTextureEx(motherShip, position, 0.0f, scale, WHITE);
                DrawText(TextFormat("%d", maxPossibleHits - hits), position.x + (motherShip.width * scale)/2 - 5, position.y, 20 , GOLD);
            }
        }
        void update(vector<Laser>& lasers, int& score){
            if (currentlySpawned){
                // despawning if it has spawned for >= spawnDuration time
                if (GetTime() >= (lastSpawned + spawnDuration)){            
                    currentlySpawned = false;
                    randomSpawnPause = GetRandomValue(20, 40);              // will spawn after a random n seconds (n > 20, < 40)
                    lastSpawned = GetTime();
                    cout << "[Game] Despawning motherShip (time over)\n";
                    // playsound...
                    return;
                }

                // checking for hits
                for (auto& laser : lasers){
                    if (laser.isActive() && CheckCollisionRecs(laser.getRect(), motherShipRect())){
                        laser.deActivate();
                        hits++;

                        if (hits >= maxPossibleHits){
                            currentlySpawned = false;
                            randomSpawnPause = GetRandomValue(20, 40);              // will spawn after a random n seconds (n > 20, < 40)
                            lastSpawned = GetTime();
                            score += scoreBoost;
                            cout << "[Game] motherShip Destructed\n";
                            // playsound
                            return;
                        }
                    }
                }

                // updating position
                if (spawnFromLeft){
                    position.x += speed;

                    if ((position.x + motherShip.width * scale) >= GetScreenWidth()){
                        speed *= -1;
                    }
                }
                else{
                    position.x -= speed;

                    if (position.x <= 0){
                        speed *= -1;
                    }
                }
            }

            else{
                if (GetTime() >= (lastSpawned + randomSpawnPause)){                          // despawning if it has spawned for >= spawnDuration time
                    currentlySpawned = true;
                    hits = 0;
                    lastSpawned = GetTime(); 

                    spawnFromLeft = (bool)GetRandomValue(0, 1);                                              // true if 1 generated, false if not
                    position.x = ((spawnFromLeft)? 0 : (GetScreenWidth() - (motherShip.width * scale)));
                    
                    if (speed < 0){ speed *= -1; }                                                           // effectively abs(speed)
                    
                    cout << "[Game] Spawning motherShip\n";
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
        SpaceShip      spaceShip; 
        Aliens         aliens;
        MotherShip     motherShip;

        int            score;
        InputMode&     movementMode;        // for storing reference of playerInputMode from settings
        vector<Laser>& lasers;              // for storing reference of lasers from spaceShip

    public:
        Playing(GameState& gameState, Settings& settings) 
        : State(gameState)
        , spaceShip("1.png")
        , score(0) 
        , movementMode(settings.getMovementMode())
        , lasers(spaceShip.getLasers())
        {}

        void init(){

        }
        void draw(){
            spaceShip.draw();
            // aliens.draw();
            motherShip.draw();
            // obstacles.draw();
        }
        void update(){
            spaceShip.update(movementMode);
            // aliens.update();
            motherShip.update(lasers, score);
            // obstacles.update();

            if (IsKeyPressed(KEY_P)){
                gameState = PAUSED;
            }
            if (WindowShouldClose()){
                gameState = CLOSEGAME;
            }
        }
};



class Paused : public State{
    private:
        Playing& playing;
        int      textSize {83};
        Sound    gameResumedSFX;
        Sound    gameStoppedSFX;

    public:
        Paused(GameState& gameState, Playing& playing) 
        : State(gameState)
        , playing(playing) 
        {
            gameResumedSFX = LoadSound("Assets/SFX/gameResumed.mp3");
            gameStoppedSFX = LoadSound("Assets/SFX/gameStopped.mp3");
        }
        ~Paused(){
            UnloadSound(gameResumedSFX);
            UnloadSound(gameStoppedSFX);
        }

        void draw(){
            // DrawText("GamePlay Paused.\n- Press \"p\" to resume.\n- Press \"x\" to finish.", GetScreenWidth() / 2 - MeasureText("GamePlay Paused.\n- Press \"p\" to resume.\n- Press \"x\" to finish.", textSize) / 2, GetScreenHeight() /2 - 3*textSize/2, textSize, GOLD);        // thats long....;  100 here is the fontsize
            DrawText("GamePlay Paused.", GetScreenWidth() / 2 - MeasureText("GamePlay Paused.", textSize) / 2, GetScreenHeight()/2 - textSize/2 - 50, textSize, GOLD);        // thats long....;  100 here is the fontsize
            DrawText("- Press \"p\" to resume.\n- Press \"x\" to finish.", GetScreenWidth() / 2 - MeasureText("- Press \"p\" to resume.\n- Press \"x\" to finish.", textSize/1.5) / 2, GetScreenHeight()/2 - textSize/2 - 50 + textSize + 30, textSize/1.5, GOLD);
        }
        void update(){
            if (IsKeyPressed(KEY_P)){
                PlaySound(gameResumedSFX);

                gameState = PLAYING;
                WaitTime(1);
            }
            if (IsKeyPressed(KEY_X)){
                PlaySound(gameStoppedSFX);
                
                gameState = MENU;
                // playing.resetAll();
                WaitTime(1);
            }
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
            //

            if (WindowShouldClose()){
                gameState = CLOSEGAME;
            }
        }
};
class CloseGame : public State{
    private:
        //

    public:
        CloseGame(GameState& gameState) : State(gameState) {}

        // not working
        void draw(){
            ClearBackground(BLANK);
            DrawText("closing", 50, 50, 50, GOLD);
        }
        void update(){
            WaitTime(3);
        }
};
class Game{
    private:
        GameState    gameState;

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
        , playing(gameState, settings)
        , paused(gameState, playing)
        , gameOver(gameState)
        , closeGame(gameState) 
        {}

        void init(){
            SetWindowOpacity(0.9);
            SetExitKey(KEY_ESCAPE);
            SetTargetFPS(63);
            InitAudioDevice();

            Image favicon = LoadImage("Assets/Favicon/2.png");
            if (favicon.data){
                SetWindowIcon(favicon);
                UnloadImage(favicon);
            }
        }

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

        // using this instead of ~Game()
        void close(){
            Sound windowCloseSFX = LoadSound("Assets/SFX/windowClose.mp3");
            PlaySound(windowCloseSFX);          // :D
            BeginDrawing();
                ClearBackground(BLANK);
                DrawText("Plz don't leave meeeee :(", GetScreenWidth()/2 - MeasureText("Plz don't leave meeeee :(", 63)/2, GetScreenHeight()/2 - 63/2, 63, GOLD);
                DrawText("Made by Ebbi, Saad, & Umair, bi-idhni-Allahi Taala :D", 23, GetScreenHeight() - 35 - 5, 35, GOLD);
            EndDrawing();
            WaitTime(2.5);
            UnloadSound(windowCloseSFX);
            
            CloseAudioDevice();
            CloseWindow();
        }
};


// Main ---

int main()
{
    // init
    InitWindow(1080, 720, "Space Invaders 👾");                 // must have this before Game game or else errors due to no openGL context
    
    Game game;
    game.init();

    while (!WindowShouldClose()){
        // updating
        game.update();

        // drawing
        BeginDrawing();

            game.draw();

        EndDrawing();
    }

    // uninit
    game.close();
}