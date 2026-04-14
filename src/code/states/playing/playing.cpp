class Playing : public State{
    private:
        SpaceShip      spaceShip; 
        Aliens         aliens;
        MotherShip     motherShip;

        int            score;
        int            enemiesDefeated;
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