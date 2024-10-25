#ifndef INIT_H
#define INIT_H

#include <string>
#include "mainconfig.h"


inline short mod(short i, short n)
{
    return (i > -1) ? i % n : n + i;
};

enum Cell : char
{
    WHITE = 'w',
    BLACK = 'b',
    WHITE_LOCKED = 'W',
    BLACK_LOCKED = 'B',
    EMPTY = 'E'
};



enum GameMode : char
{
    PvP,
    PvAI
};

extern MainConfig mainConfig;

#endif // INIT_H
