#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <cstdint>
#include <vector>
#include "move.h"

const int Infinity = INT32_MAX;

// using Board = std::vector<std::vector<Color>>;



class State {
private:

    Cell board[3][8];
    short whitePawnsLeft;      // How many pieces are left in white's possession
    short blackPawnsLeft;      // How many pieces are left in black's possession
    short whitePawnsPut;       // How many white pieces were put on the board
    short blackPawnsPut;       // How many black pieces were put on the board
    Cell turn;                // Whose turn is it now
    int heuristicValue;

public:
    // Constructor : Initializes all the cell as empty
    State() {
        for (short i = 0; i < 3; i++)
        {
            for (short j = 0; j < 8; j++)
            {
                board[i][j] = EMPTY;
            };
        };
        turn = WHITE;
        whitePawnsLeft = 9;
        blackPawnsLeft = 9;
        whitePawnsPut = 0;
        blackPawnsPut = 0;
    };

    // Destructor
    ~State() {};


    void evaluate(Cell);

    void update(Move&);

    Cell checkWin();

    short &getPawnsLeft(Cell);
    short getPawnsPut(Cell);
    Cell getTurn();

    void putPawn(Cell, short, short);
    void removePawn(Cell, short, short);
    void setTurn(Cell);
    bool isLocked(Cell, short, short);
    void lock(short, short);
    void unlock(Cell, short, short);
    Cell &getCellValue(short, short);
    Move getMove(State);

    int getHeuristicValue();
    State alphaBeta(int, Cell, int = -Infinity, int = Infinity, bool = true);
    State minMax(int, Cell, bool = true);
    std::vector<State> createChildList();

    // Display the board in the console
    void display();

};

#endif
