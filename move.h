#ifndef MOVE_H
#define MOVE_H


#include "init.hpp"

class Move {
private:
    short source_i; // Coordinates of the source position (in case we're moving a pawn from one place to another)
    short source_j;
    short dest_i;   // Coordinates of the target position
    short dest_j;
    short remove_i; // Coordinates of the oppenent pawn that we want to remove (in case we have the right to do so)
    short remove_j;
    Cell turn;     // Who will be playing this very move
public:
    Move() {
        source_i = 3;
        source_j = 3;
        remove_i = 3;
        remove_j = 3;
    };

    Move(short d_i, short d_j, short s_i = 3, short s_j = 3,
         Cell c = EMPTY, short r_i = 3, short r_j = 3):

        source_i(s_i), source_j(s_j), dest_i(d_i), dest_j(d_j),
        turn(c), remove_i(r_i), remove_j(r_j)

        {};

    // Get attributes
    short &get_source_i();
    short &get_source_j();
    short &get_dest_i();
    short &get_dest_j();
    short &get_remove_i();
    short &get_remove_j();
    Cell &getColor();

    // Set attributes
    void set_source_i(short);
    void set_source_j(short);
    void set_dest_i(short);
    void set_dest_j(short);
    void set_remove_i(short);
    void set_remove_j(short);
    void setColor(Cell);
};

#endif // MOVE_H
