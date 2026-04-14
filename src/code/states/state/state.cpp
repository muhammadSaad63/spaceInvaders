
class State{                                                        // an abstract class to be inherited by all gameState subclasses
    protected:
        GameState&  gameState;

    public:
        State(GameState& gameState) : gameState(gameState) {}

        virtual void draw()   = 0;
        virtual void update() = 0;
};
