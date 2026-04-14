
class GameOver : public State{
    private:
        DataBase& dataBase;
        // GameData& gameData;

    public:
        GameOver(GameState& gameState, DataBase& dataBase) 
        : State(gameState)
        , dataBase(dataBase)
        {}

        void draw(){

        }
        void update(){
            //

            if (WindowShouldClose()){
                gameState = CLOSEGAME;
            }
        }
};