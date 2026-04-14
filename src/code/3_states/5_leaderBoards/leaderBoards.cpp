class LeaderBoards : public State{
    private:
        DataBase& dataBase;
        // GameData& gameData;

    public:
        LeaderBoards(GameState& gameState, DataBase& dataBase) 
        : State(gameState)
        , dataBase(dataBase)
        {}

        void draw(){

        }
        void update(){

        }
};