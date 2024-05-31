#ifndef MOVE_MANAGER_H /* Include guard */
#define MOVE_MANAGER_H

#include "position.h"

void MakeMove(Position *pos, int move);

// preserve board state
#define copy_board()           \
    Position pos_copy[1]; \
    memcpy(pos_copy, pos, sizeof(Position));

// restore board state
#define take_back() \
    memcpy(pos, pos_copy, sizeof(Position));
    
#endif