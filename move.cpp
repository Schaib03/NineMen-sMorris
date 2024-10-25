#include "move.h"

void Move::set_source_i(short x)
{
    source_i = x;
}

void Move::set_source_j(short x)
{
    source_j = x;
}

void Move::set_dest_i(short x)
{
    dest_i = x;
}

void Move::set_dest_j(short x)
{
    dest_j = x;
}

void Move::set_remove_i(short x)
{
    remove_i = x;
}

void Move::set_remove_j(short x)
{
    remove_j = x;
}

void Move::setColor(Cell c)
{
    turn = c;
}

short &Move::get_source_i()
{
    return source_i;
}

short &Move::get_source_j()
{
    return source_j;
}

short &Move::get_dest_i()
{
    return dest_i;
}

short &Move::get_dest_j()
{
    return dest_j;
}

short &Move::get_remove_i()
{
    return remove_i;
}

short &Move::get_remove_j()
{
    return remove_j;
}

Cell &Move::getColor()
{
    return turn;
}
