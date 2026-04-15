#include "shop.hpp"


class Shop : public State{
    private:
        // DataBase& dataBase;
        // GameData& gameData;

    public:
        Shop(GameState& gameState) 
        : State(gameState)
        // , dataBase(dataBase)
        {}

        void draw(){

        }
        void update(){

        }
};