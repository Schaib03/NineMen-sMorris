#ifndef PLAYER_H
#define PLAYER_H

#include "init.hpp"
#include "move.h"
#include "game.h"


class Player
{
    public:
        virtual Move getNextMove() {
            Move m;
            return m;
        };
};

class HumanPlayer : public Player
{
    public:
        HumanPlayer() {};
        Move getNextMove(Game);
};

class AIPlayer : public Player
{
    private:
        int diff;
    public:
        AIPlayer(int = 1);
        Move getNextMove(Game);
        void setDifficulty(int);
};

#endif  // PLAYER_H
