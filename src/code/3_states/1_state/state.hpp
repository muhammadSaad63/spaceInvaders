#pragma once


#include "../../1_core/enums/gameState.hpp"


class State{                                                        // an abstract class / interface to be inherited by all gameState subclasses
    protected:
        GameState&  gameState;

    public:
        State(GameState& gameState) : gameState(gameState) {}
        virtual ~State() = default;

        virtual void draw()   = 0;
        virtual void update() = 0;
};