#include "state.h"

#include <QDebug>


short &State::getPawnsLeft(Cell c)
{
    return (c == WHITE) ? whitePawnsLeft : blackPawnsLeft;
}


short State::getPawnsPut(Cell c)
{
    return (c == WHITE) ? whitePawnsPut : blackPawnsPut;
}


Cell State::getTurn()
{
    return turn;
}


void State::putPawn(Cell c, short i, short j)
{
    board[i][j] = c;
    if (c == WHITE)
    {
        if (whitePawnsPut < 9)
        {
            whitePawnsPut++;
            return;
        };
        whitePawnsLeft++;
        return;
    };
    if (blackPawnsPut < 9)
    {
        blackPawnsPut++;
        return;
    };
    blackPawnsLeft++;
    return;

}


void State::removePawn(Cell c, short i, short j)
{
    if (c == WHITE)
    {
        whitePawnsLeft--;
    }
    else
    {
        blackPawnsLeft--;
    };
    board[i][j] = EMPTY;
}


void State::setTurn(Cell c)
{
    turn = c;
}


bool State::isLocked(Cell c, short i, short j)
{
    // std::cout << c << "\n";
    if (c == WHITE)
    {
        return (board[i][j] == WHITE_LOCKED);
    }
    else if (c == BLACK)
    {
        return (board[i][j] == BLACK_LOCKED);
    };
    return false;
}


void State::lock(short i, short j)
{
    // std::cout << "locking .. \n";
    if (board[i][j] == WHITE)
    {
        board[i][j] = WHITE_LOCKED;
    }
    else if (board[i][j] == BLACK)
    {
        board[i][j] = BLACK_LOCKED;
    };
}


void State::unlock(Cell c, short i, short j)
{
    if (isLocked(c, i, j))
    {
        board[i][j] = c;
    };
}


Move State::getMove(State nextState)
{
    // Compare between "this" state and the next one to conclude the move that was done between them
    Move m;
    m.setColor(turn);
    for (short i = 0; i < 3; i++)
    {
        for (short j = 0; j < 8; j++)
        {
            if ((nextState.board[i][j] == turn || nextState.isLocked(turn, i, j)) && this->board[i][j] == EMPTY)
            {
                m.set_dest_i(i);
                m.set_dest_j(j);
            };
            if ((this->board[i][j] == turn || this->isLocked(turn, i, j)) && nextState.board[i][j] == EMPTY)
            {
                m.set_source_i(i);
                m.set_source_j(j);
            };
            if ((this->board[i][j] == nextState.turn || this->isLocked(nextState.turn, i, j)) && nextState.board[i][j] == EMPTY)
            {
                m.set_remove_i(i);
                m.set_remove_j(j);
            };
        };
    };
    return m;
}


Cell &State::getCellValue(short i, short j)
{
    return board[i][j];
}


void State::evaluate(Cell maxTurn)
{
    // Evaluates the current state using the heuristic function

    Cell minTurn = (maxTurn == WHITE) ? BLACK : WHITE;
    if (checkWin() == maxTurn)
    {
        heuristicValue = Infinity;
        return;
    };
    if (checkWin() == minTurn)
    {
        heuristicValue = -Infinity;
        return;
    };
    int maxAvailableLines = 0;
    int minAvailableLines = 0;
    int temp1 = 1, temp2 = 1;

    // Parcours des lignes
    for (short r = 0; r < 3; r++) {
        for (short i = 0; i < 8; i += 2)
        {
            temp1 = 1;
            temp2 = 1;
            for (short j = 0; j < 3; j++)
            {
                temp1 *= (board[r][(i + j) % 8] == maxTurn || board[r][(i + j) % 8] == EMPTY || isLocked(maxTurn, i,(i + j) % 8)) ? 1 : 0;
                temp2 *= (board[r][(i + j) % 8] == minTurn || board[r][(i + j) % 8] == EMPTY || isLocked(minTurn, i,(i + j) % 8)) ? 1 : 0;
            };
            maxAvailableLines += temp1;
            minAvailableLines += temp2;
        };
    };

    for (short i = 1; i < 8; i += 2)
    {
        temp1 = 1;
        temp2 = 1;
        for (short j = 0; j < 3; j++)
        {
            temp1 *= (board[j][i] == maxTurn || board[j][i] == EMPTY || isLocked(maxTurn, j, i)) ? 1 : 0;
            temp2 *= (board[j][i] == minTurn || board[j][i] == EMPTY || isLocked(minTurn, j, i)) ? 1 : 0;
        };
        maxAvailableLines += temp1;
        minAvailableLines += temp2;
    };



    // Calcul de la valeur heuristique
    int h = maxAvailableLines - minAvailableLines;
    h += (maxTurn == WHITE) ? 100 * (whitePawnsLeft - blackPawnsLeft) : 100 * (blackPawnsLeft - whitePawnsLeft);
    heuristicValue = h;
    qDebug() << "El heuristicos :" << heuristicValue;
    return;
}


void State::display()
{
    // Prints the current state on the console

    qDebug().nospace() << board[0][0] << "--------------" << board[0][1] << "--------------" << board[0][2] << "\n";
    qDebug().nospace() << "|              |              |\n";
    qDebug().nospace() << "|    " << board[1][0] << "---------" << board[1][1] << "---------" << board[1][2] << "    |\n";
    qDebug().nospace() << "|    |         |         |    |\n";
    qDebug().nospace() << "|    |    " << board[2][0] << "----" << board[2][1] << "----" << board[2][2] << "    |    |\n";
    qDebug().nospace() << "|    |    |         |    |    |\n";
    qDebug().nospace() << board[0][7] << "----" << board[1][7] << "----" << board[2][7] << "         " << board[2][3] << "----" << board[1][3] << "----" << board[0][3] << "\n";
    qDebug().nospace() << "|    |    |         |    |    |\n";
    qDebug().nospace() << "|    |    " << board[2][6] << "----" << board[2][5] << "----" << board[2][4] << "    |    |\n";
    qDebug().nospace() << "|    |         |         |    |\n";
    qDebug().nospace() << "|    " << board[1][6] << "---------" << board[1][5] << "---------" << board[1][4] << "    |\n";
    qDebug().nospace() << "|              |              |\n";
    qDebug().nospace() << board[0][6] << "--------------" << board[0][5] << "--------------" << board[0][4] << "\n";

    return;
}


void State::update(Move &m)
{
    Cell nextTurn = (m.getColor() == WHITE) ? BLACK : WHITE;
    putPawn(m.getColor(), m.get_dest_i(), m.get_dest_j());
    if (m.get_source_i() != 3)
    {
        removePawn(m.getColor(), m.get_source_i(), m.get_source_j());
        // std::cout << "moved a pawn\n";
    };
    if (m.get_remove_i() != 3)
    {
        removePawn(nextTurn, m.get_remove_i(), m.get_remove_j());
        // std::cout << "removed a pawn\n";
    };

    for (short i = 0; i < 3; i++)
    {
        for (short j = 0; j < 8; j++)
        {
            // std::cout << "Unlock sequence " << i << " " << j << "\n";
            if (j % 2 == 0 && !((board[i][j] == turn || isLocked(turn, i, j))
                && (board[i][(j + 1) % 8] == turn || isLocked(turn, i, (j + 1) % 8))
                && (board[i][(j + 2) % 8] == turn || isLocked(turn, i, (j + 2) % 8))))
            {
                unlock(turn, i, j);
                unlock(turn, i, (j + 1) % 8);
                unlock(turn, i, (j + 2) % 8);
            };
            if (j % 2 == 1 && !((board[i][j] == turn || isLocked(turn, i, j))
                && (board[(i + 1) % 3][j] == turn || isLocked(turn, (i + 1) % 3, j))
                && (board[(i + 2) % 3][j] == turn || isLocked(turn, (i + 2) % 3, j))))
            {
                unlock(turn, i, j);
                unlock(turn, (i + 1) % 3, j);
                unlock(turn, (i + 2) % 3, j);
            };
        };
    };
    for (short i = 0; i < 3; i++)
    {
        for (short j = 0; j < 8; j++)
        {
            // std::cout << "lock sequence " << i << " " << j << "\n";
            if (j % 2 == 0 && (board[i][j] == turn || isLocked(turn, i, j))
                && (board[i][(j + 1) % 8] == turn || isLocked(turn, i, (j + 1) % 8))
                && (board[i][(j + 2) % 8] == turn || isLocked(turn, i, (j + 2) % 8)))
            {
                lock(i, j);
                lock(i, (j + 1) % 8);
                lock(i, (j + 2) % 8);
            };
            if (j % 2 == 1 && (board[i][j] == turn || isLocked(turn, i, j))
                && (board[(i + 1) % 3][j] == turn || isLocked(turn, (i + 1) % 3, j))
                && (board[(i + 2) % 3][j] == turn || isLocked(turn, (i + 2) % 3, j)))
            {
                lock(i, j);
                lock((i + 1) % 3, j);
                lock((i + 2) % 3, j);
            };
        };
    };
    setTurn(nextTurn);
    return;
}


Cell State::checkWin()
{
    if (whitePawnsLeft == 2)
    {
        qDebug() << "Black wins!\n";
        return BLACK;
    };
    if (blackPawnsLeft == 2)
    {
        qDebug() << "White wins !\n";
        return WHITE;
    };
    if (blackPawnsPut < 9 || whitePawnsPut < 9 || blackPawnsLeft == 3 || whitePawnsLeft == 3)
    {
        return EMPTY;
    };
    for (short i = 0; i < 3; i++)
    {
        for (short j = 0; j < 8; j++)
        {
            if (board[i][j] == turn || isLocked(turn, i, j))
            {
                if (board[i][(j + 1) % 8] == EMPTY)
                {
                    return EMPTY;
                };
                if (board[i][mod(j - 1, 8)] == EMPTY)
                {
                    return EMPTY;
                };
                if (j % 2 == 1)
                {
                    if (i > 0)
                    {
                        if (board[i - 1][j] == EMPTY)
                        {
                            return EMPTY;
                        };
                    };
                    if (i < 2)
                    {
                        if (board[i + 1][j] == EMPTY)
                        {
                            return EMPTY;
                        };
                    };
                };
            };
        };
    };
    return (turn == WHITE) ? BLACK : WHITE;
}


std::vector<State> State::createChildList()
{
    Move m;
    m.setColor(turn);
    std::vector<State> childList;
    Cell nextTurn = (turn == WHITE) ? BLACK : WHITE;
    // TASK: generate child State based on current State
    if (blackPawnsPut < 9)
    {
        for (short i = 0; i < 3; i++)
        {
            for (short j = 0; j < 8; j += 2)
            {
                if (board[i][j] == EMPTY)
                {
                    m.set_dest_i(i);
                    m.set_dest_j(j);
                    if ((board[i][j + 1] == turn || isLocked(turn, i, j + 1)) && (board[i][(j + 2) % 8] == turn || isLocked(turn, i, (j + 2) % 8)))
                    {
                        for (short i = 0; i < 3; i++)
                        {
                            for (short j = 0; j < 8; j++)
                            {
                                if (board[i][j] == nextTurn)
                                {
                                    State childState = *this;
                                    m.set_remove_i(i);
                                    m.set_remove_j(j);
                                    childState.update(m);
                                    m.set_remove_i(3);
                                    childList.push_back(childState);
                                };
                            };
                        };
                    }
                    else if ((board[i][j - 1] == turn || isLocked(turn, i, j - 1)) && (board[i][mod((j - 2), 8)] == turn || isLocked(turn, i, mod((j - 2), 8))))
                    {
                        for (short i = 0; i < 3; i++)
                        {
                            for (short j = 0; j < 8; j++)
                            {
                                if (board[i][j] == nextTurn)
                                {
                                    State childState = *this;
                                    m.set_remove_i(i);
                                    m.set_remove_j(j);
                                    childState.update(m);
                                    m.set_remove_i(3);
                                    childList.push_back(childState);
                                };
                            };
                        };
                    }
                    else
                    {
                        State childState = *this;
                        childState.update(m);
                        childList.push_back(childState);
                    };
                };
            };
            for (short j = 1; j < 8; j += 2)
            {
                if (board[i][j] == EMPTY)
                {
                    m.set_dest_i(i);
                    m.set_dest_j(j);
                    if ((board[(i + 1) % 3][j] == turn || isLocked(turn, (i + 1) % 3, j)) && (board[(i + 2) % 3][j] == turn || isLocked(turn, (i + 2) % 3, j)))
                    {
                        for (short i = 0; i < 3; i++)
                        {
                            for (short j = 0; j < 8; j++)
                            {
                                if (board[i][j] == nextTurn)
                                {
                                    State childState = *this;
                                    // n.removePawn(nextTurn, i, j);
                                    m.set_remove_i(i);
                                    m.set_remove_j(j);
                                    childState.update(m);
                                    m.set_remove_i(3);
                                    childList.push_back(childState);
                                };
                            };
                        };
                    }
                    else if ((board[i][j - 1] == turn || isLocked(turn, i, j - 1)) && (board[i][(j + 1) % 8] == turn || isLocked(turn, i, (j + 1) % 8)))
                    {
                        for (short i = 0; i < 3; i++)
                        {
                            for (short j = 0; j < 8; j++)
                            {
                                if (board[i][j] == nextTurn)
                                {
                                    State childState = *this;
                                    // n.removePawn(nextTurn, i, j);
                                    m.set_remove_i(i);
                                    m.set_remove_j(j);
                                    childState.update(m);
                                    m.set_remove_i(3);
                                    childList.push_back(childState);
                                };
                            };
                        };
                    }
                    else
                    {
                        State childState = *this;
                        childState.update(m);
                        childList.push_back(childState);
                    };
                };
            };
        };
        return childList;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if ((turn == WHITE && whitePawnsLeft == 3) || (turn == BLACK && blackPawnsLeft == 3))
    {
        for (short r = 0; r < 3; r++) // r for rows
        {
            for (short c = 0; c < 8; c++) // c for columns
            {
                if (board[r][c] != turn && !isLocked(turn, r, c)) { continue; };
                for (short i = 0; i < 3; i++)
                {
                    for (short j = 0; j < 8; j += 2)
                    {
                        if (board[i][j] == EMPTY)
                        {
                            m.set_source_i(r);
                            m.set_source_j(c);
                            m.set_dest_i(i);
                            m.set_dest_j(j);

                            if ((board[i][j + 1] == turn || isLocked(turn, i, j + 1)) && (board[i][(j + 2) % 8] == turn || isLocked(turn, i, (j + 2) % 8)))
                            {
                                for (short i = 0; i < 3; i++)
                                {
                                    for (short j = 0; j < 8; j++)
                                    {
                                        if (board[i][j] == nextTurn)
                                        {
                                            State childState = *this;
                                            m.set_remove_i(i);
                                            m.set_remove_j(j);
                                            childState.update(m);
                                            m.set_remove_i(3);
                                            childList.push_back(childState);
                                        };
                                    };
                                };
                            }
                            else if ((board[i][j - 1] == turn || isLocked(turn, i, j - 1)) && (board[i][mod((j - 2), 8)] == turn || isLocked(turn, i, mod((j - 2), 8))))
                            {
                                for (short i = 0; i < 3; i++)
                                {
                                    for (short j = 0; j < 8; j++)
                                    {
                                        if (board[i][j] == nextTurn)
                                        {
                                            State childState = *this;
                                            m.set_remove_i(i);
                                            m.set_remove_j(j);
                                            childState.update(m);
                                            m.set_remove_i(3);
                                            childList.push_back(childState);
                                        };
                                    };
                                };
                            }
                            else
                            {
                                State childState = *this;
                                childState.update(m);
                                childList.push_back(childState);
                            };
                        };
                    };
                    for (short j = 1; j < 8; j += 2)
                    {
                        if (board[i][j] == EMPTY)
                        {
                            m.set_source_i(r);
                            m.set_source_j(c);
                            m.set_dest_i(i);
                            m.set_dest_j(j);

                            if ((board[(i + 1) % 3][j] == turn || isLocked(turn, (i + 1) % 3, j)) && (board[(i + 2) % 3][j] == turn || isLocked(turn, (i + 2) % 3, j)))
                            {
                                for (short i = 0; i < 3; i++)
                                {
                                    for (short j = 0; j < 8; j++)
                                    {
                                        if (board[i][j] == nextTurn)
                                        {
                                            State childState = *this;
                                            // n.removePawn(nextTurn, i, j);
                                            m.set_remove_i(i);
                                            m.set_remove_j(j);
                                            childState.update(m);
                                            m.set_remove_i(3);
                                            childList.push_back(childState);
                                        };
                                    };
                                };
                            }
                            else if ((board[i][j - 1] == turn || isLocked(turn, i, j - 1)) && (board[i][(j + 1) % 8] == turn || isLocked(turn, i, (j + 1) % 8)))
                            {
                                for (short i = 0; i < 3; i++)
                                {
                                    for (short j = 0; j < 8; j++)
                                    {
                                        if (board[i][j] == nextTurn)
                                        {
                                            State childState = *this;
                                            // n.removePawn(nextTurn, i, j);
                                            m.set_remove_i(i);
                                            m.set_remove_j(j);
                                            childState.update(m);
                                            m.set_remove_i(3);
                                            childList.push_back(childState);
                                        };
                                    };
                                };
                            }
                            else
                            {
                                State childState = *this;
                                childState.update(m);
                                childList.push_back(childState);
                            };
                        };
                    };
                };
            };
        };
        return childList;
    };

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////

    for (short r = 0; r < 3; r++) // r for rows
    {
        for (short c = 0; c < 8; c += 2) // c for columns
        {
            if (board[r][c] != turn && !isLocked(turn, r, c))
            {
                continue;
            };

            if (board[r][c + 1] == EMPTY)
            {
                m.set_source_i(r);
                m.set_source_j(c);
                m.set_dest_i(r);
                m.set_dest_j(c + 1);
                short i = r, j = c + 1;
                if ((board[(i + 1) % 3][j] == turn || isLocked(turn, (i + 1) % 3, j))
                    && (board[(i + 2) % 3][j] == turn || isLocked(turn, (i + 2) % 3, j)))
                {
                    for (short i = 0; i < 3; i++)
                    {
                        for (short j = 0; j < 8; j++)
                        {
                            if (board[i][j] == nextTurn)
                            {
                                State childState = *this;
                                m.set_remove_i(i);
                                m.set_remove_j(j);
                                childState.update(m);
                                m.set_remove_i(3);
                                childList.push_back(childState);
                            };
                        };
                    };
                }
                else
                {
                    State childState = *this;
                    childState.update(m);
                    childList.push_back(childState);
                };
            };

            if (board[r][mod((c - 1), 8)] == EMPTY)
            {
                m.set_source_i(r);
                m.set_source_j(c);
                m.set_dest_i(r);
                m.set_dest_j(mod((c - 1), 8));
                short i = r, j = mod((c - 1), 8);
                if ((board[(i + 1) % 3][j] == turn || isLocked(turn, (i + 1) % 3, j))
                    && (board[(i + 2) % 3][j] == turn || isLocked(turn, (i + 2) % 3, j)))
                {
                    for (short i = 0; i < 3; i++)
                    {
                        for (short j = 0; j < 8; j++)
                        {
                            if (board[i][j] == nextTurn)
                            {
                                State childState = *this;
                                m.set_remove_i(i);
                                m.set_remove_j(j);
                                childState.update(m);
                                m.set_remove_i(3);
                                childList.push_back(childState);
                            };
                        };
                    };
                }
                else
                {
                    State childState = *this;
                    childState.update(m);
                    childList.push_back(childState);
                };
            };
        };
        for (short c = 1; c < 8; c += 2) // c for columns
        {
            if (board[r][c] != turn && !isLocked(turn, r, c))
            {
                continue;
            };
            if (board[r][(c + 1) % 8] == EMPTY)
            {
                m.set_source_i(r);
                m.set_source_j(c);
                m.set_dest_i(r);
                m.set_dest_j((c + 1) % 8);
                short i = r, j = (c + 1) % 8;
                if ((board[i][j + 1] == turn || isLocked(turn, i, j + 1))
                    && (board[i][(j + 2) % 8] == turn || isLocked(turn, i, (j + 2) % 8)))
                {
                    for (short i = 0; i < 3; i++)
                    {
                        for (short j = 0; j < 8; j++)
                        {
                            if (board[i][j] == nextTurn)
                            {
                                State childState = *this;
                                m.set_remove_i(i);
                                m.set_remove_j(j);
                                childState.update(m);
                                m.set_remove_i(3);
                                childList.push_back(childState);
                            };
                        };
                    };
                }
                else
                {
                    State childState = *this;
                    childState.update(m);
                    childList.push_back(childState);
                };
            };

            //////////////////////////////////////////////////////////////////////////////////////////////////////

            if (board[r][c - 1] == EMPTY)
            {
                m.set_source_i(r);
                m.set_source_j(c);
                m.set_dest_i(r);
                m.set_dest_j(c - 1);
                short i = r, j = c - 1;
                if ((board[i][mod(j - 1, 8)] == turn || isLocked(turn, i, mod(j - 1, 8)))
                    && (board[i][mod(j - 2, 8)] == turn || isLocked(turn, i, mod(j - 2, 8))))
                {
                    for (short i = 0; i < 3; i++)
                    {
                        for (short j = 0; j < 8; j++)
                        {
                            if (board[i][j] == nextTurn)
                            {
                                State childState = *this;
                                m.set_remove_i(i);
                                m.set_remove_j(j);
                                childState.update(m);
                                m.set_remove_i(3);
                                childList.push_back(childState);
                            };
                        };
                    };
                }
                else
                {
                    State childState = *this;
                    childState.update(m);
                    childList.push_back(childState);
                };
            };

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            if (r < 2 && board[r + 1][c] == EMPTY)
            {
                m.set_source_i(r);
                m.set_source_j(c);
                m.set_dest_i(r + 1);
                m.set_dest_j(c);
                short i = r + 1, j = c;
                if ((board[i][j - 1] == turn || isLocked(turn, i, j - 1))
                    && (board[i][(j + 1) % 8] == turn || isLocked(turn, i, (j + 1) % 8)))
                {
                    for (short i = 0; i < 3; i++)
                    {
                        for (short j = 0; j < 8; j++)
                        {
                            if (board[i][j] == nextTurn)
                            {
                                State childState = *this;
                                // n.removePawn(nextTurn, i, j);
                                m.set_remove_i(i);
                                m.set_remove_j(j);
                                childState.update(m);
                                m.set_remove_i(3);
                                childList.push_back(childState);
                            };
                        };
                    };
                }
                else
                {
                    State childState = *this;
                    childState.update(m);
                    childList.push_back(childState);
                };
            };

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            if (r > 0 && board[r - 1][c] == EMPTY)
            {
                m.set_source_i(r);
                m.set_source_j(c);
                m.set_dest_i(r - 1);
                m.set_dest_j(c);
                short i = r - 1, j = c;
                if (m.get_source_j() != j - 1
                    && m.get_source_j() != (j + 2) % 8
                    &&(board[i][j - 1] == turn || isLocked(turn, i, j - 1))
                    && (board[i][(j + 1) % 8] == turn || isLocked(turn, i, (j + 1) % 8)))
                {
                    for (short i = 0; i < 3; i++)
                    {
                        for (short j = 0; j < 8; j++)
                        {
                            if (board[i][j] == nextTurn)
                            {
                                State childState = *this;
                                m.set_remove_i(i);
                                m.set_remove_j(j);
                                childState.update(m);
                                m.set_remove_i(3);
                                childList.push_back(childState);
                            };
                        };
                    };
                }
                else
                {
                    State childState = *this;
                    childState.update(m);
                    childList.push_back(childState);
                };
            };
        };
    };
    return childList;
}


int State::getHeuristicValue()
{
    return heuristicValue;
}


State State::alphaBeta(int depth, Cell maxTurn, int alpha, int beta, bool maximizingPlayer)
{
    // std::cout << "depth : " << depth << "\n";
    if (depth == 0 || this->checkWin() != EMPTY)
    {
        this->evaluate(maxTurn);
        return *this;
    };
    int value;
    std::vector<State> childList = this->createChildList();
    State bestChild = childList.front();
    if (maximizingPlayer)
    {
        // std::cout << "Max player";
        value = -Infinity;
        for (State &s: childList)
        {
            // s.display();
            State tempState = s.alphaBeta(depth - 1, maxTurn, alpha, beta, false);
            int temp = tempState.getHeuristicValue();
            // qDebug() << "heuristic : " << temp << "\n";
            if (temp > value)
            {
                value = temp;
                bestChild = s;
            };
            if (value >= beta)
            {
                break;
            };

            if (value > alpha)
            {
                alpha = value;
            };
        };
        return bestChild;
    }
    else
    {
        value = Infinity;
        for (State &s: childList)
        {
            State tempState = s.alphaBeta(depth - 1, maxTurn, alpha, beta, true);
            int temp = tempState.getHeuristicValue();
            if (temp < value)
            {
                value = temp;
                bestChild = s;
            };
            if (value <= alpha)
            {
                break;
            };

            if (value < beta)
            {
                beta = value;
            };
        };
        return bestChild;
    };
}


State State::minMax(int depth, Cell maxTurn, bool maximizingPlayer)
{
    // std::cout << "depth : " << depth << "\n";
    if (depth == 0 || this->checkWin() != EMPTY)
    {
        this->evaluate(maxTurn);
        return *this;
    };
    int value;
    std::vector<State> childList = this->createChildList();
    State bestChild = childList.front();
    if (maximizingPlayer)
    {
        // std::cout << "Max player";
        value = -Infinity;
        for (State &s: childList)
        {
            // s.display();
            State tempState = s.minMax(depth - 1, maxTurn, false);
            int temp = tempState.getHeuristicValue();
            std::cout << "heuristic : " << temp << "\n";
            if (temp > value)
            {
                value = temp;
                bestChild = s;
            };
        };
        return bestChild;
    }
    else
    {
        value = Infinity;
        for (State &s: childList)
        {
            State tempState = s.minMax(depth - 1, maxTurn, true);
            int temp = tempState.getHeuristicValue();
            if (temp < value)
            {
                value = temp;
                bestChild = s;
            };
        };
        return bestChild;
    };
}
