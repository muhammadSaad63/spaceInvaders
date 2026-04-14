
class CloseGame : public State{
    private:
        //

    public:
        CloseGame(GameState& gameState) : State(gameState) {}

        // not working
        void draw(){
            DrawText("closing", 50, 50, 50, GOLD);
        }
        void update(){
            WaitTime(3);
        }
};