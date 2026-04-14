class History : public State{
    private:
        DataBase& dataBase;
        // GameData& gameData;

    public:
        History(GameState& gameState, DataBase& dataBase) 
        : State(gameState)
        , dataBase(dataBase)
        {}

        void draw(){

        }
        void update(){

        }
};