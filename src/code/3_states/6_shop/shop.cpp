class Shop : public State{
    private:
        DataBase& dataBase;
        // GameData& gameData;

    public:
        Shop(GameState& gameState, DataBase& dataBase) 
        : State(gameState)
        , dataBase(dataBase)
        {}

        void draw(){

        }
        void update(){

        }
};