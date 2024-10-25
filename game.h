#ifndef GAME_H
#define GAME_H

#include <vector>
#include "state.h"
#include <fstream>
#include <QString>

class Game {
    private:
        unsigned int moveCount;
        State currentState;          // Current board
        std::vector<State> states;   // Vector of all boards since beginning of the game
        Cell turn;
        Cell winner;
        GameMode mode;
        Cell playerColor;
        int diff; // game difficulty
    public:

        // Constructor
        Game(Cell = WHITE);

        void load(QString filename);

        void save();

        void makeMove(Move);

        Cell &getcurrentTurn();

        unsigned int &getMoveCount();

        Cell checkWin();

        State &getCurrentState();

        void setGameMode(GameMode);

        GameMode getGameMode();

        void setDifficulty(int);

        int getDifficulty();

        Cell getPlayerColor();

        void setPlayerColor(Cell);

};

#endif
