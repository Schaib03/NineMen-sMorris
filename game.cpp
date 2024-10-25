#include "game.h"
#include <QDebug>


// Constructor
Game::Game(Cell c) : turn(c)
{
    moveCount = 0;
    currentState = State();
    states.clear();
    states.push_back(currentState);
    winner = EMPTY;
    mode = PvP;
};


// Load a game from a file
void Game::load(QString s)
{
    std::ifstream in;
    std::string fileName = s.toStdString();
    in.open(fileName, std::ios::in | std::ios::binary);
    if (!in)
    {
        qDebug() << "file couldn't be opened :" << fileName;
        return;
    };
    State elem;
    in.read((char *) &mode, sizeof(mode));
    in.read((char *) &playerColor, sizeof(playerColor));
    in.read((char *) &diff, sizeof(diff));
    in.read((char *) &moveCount, sizeof(moveCount));
    states.clear();
    while (in.read((char *)&elem, sizeof(elem)))
    {
        qDebug() << "loaded a state";
        states.push_back(elem);
    };
    in.close();
    currentState = states.back();
    currentState.display();
    winner = currentState.checkWin();
    turn = currentState.getTurn();
    return;
}


// Save a game to a file with a unique id (derived from the date of saving)
void Game::save()
{
    std::ofstream out;
    std::string filename = "../../savegames/savegame_";
    mainConfig.incrementSaveCount();
    filename.append(std::to_string(mainConfig.getSaveCount()));
    filename.append(".txt");
    out.open(filename, std::ios::out | std::ios::binary);
    out.write((char *) &mode, sizeof(mode));
    out.write((char *) &playerColor, sizeof(playerColor));
    out.write((char *) &diff, sizeof(diff));
    out.write((char *) &moveCount, sizeof(moveCount));
    for (auto &state : states)
    {
        out.write((char *) &state, sizeof(state));
        qDebug() << "wrote a state";
    };
    out.close();
}

Cell &Game::getcurrentTurn()
{
    return turn;
}


unsigned int &Game::getMoveCount()
{
    return moveCount;
}

// Apply a move, switch turns and move to another state
void Game::makeMove(Move m)
{
    currentState.update(m);
    turn = currentState.getTurn();
    moveCount++;
    states.push_back(currentState);
}

// Check who is the winner (should one exist, otherwise return empty)
Cell Game::checkWin()
{
    return currentState.checkWin();
}

State& Game::getCurrentState()
{
    return currentState;
}

GameMode Game::getGameMode()
{
    return mode;
}

void Game::setGameMode(GameMode m)
{
    mode = m;
}

void Game::setDifficulty(int d)
{
    diff = d;
}

int Game::getDifficulty()
{
    return diff;
}

Cell Game::getPlayerColor()
{
    return playerColor;
}

void Game::setPlayerColor(Cell c)
{
    playerColor = c;
}
