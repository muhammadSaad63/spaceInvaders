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
            spaceShip = LoadTexture(TextFormat("../assets/graphics/player/spaceShips/%s", fileName.c_str()));
            
            // returns true if the texture is loaded into memory; alternatively coudlve used "if (spaceShip.id)"
            cout << "[GAME] SpaceShip texture (" << fileName << (IsTextureValid(spaceShip)? ") has" : ") has NOT") << " loaded properly.\n";
        }

    public:
        SpaceShip(const string& fileName){
            loadShip(fileName);

            scale = 0.1f;
            bottomOffset = 50;

            posX = (GetScreenWidth() / 2 - (spaceShip.width  * scale) / 2);
            posY = (GetScreenHeight()    - (spaceShip.height * scale) - bottomOffset); 

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
            posX = (GetScreenWidth() / 2 - (spaceShip.width  * scale) / 2);
            posY = (GetScreenHeight()    - (spaceShip.height * scale) - bottomOffset); 
        }
        vector<Laser>& getLasers(){
            return lasers;
        }
};
