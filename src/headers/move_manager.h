#ifndef MOVE_MANAGER_H /* Include guard */
#define MOVE_MANAGER_H

#include "position.h"

void MakeMove(Position *pos, int move);

// preserve board state
#define copy_board()           \
    Position position_copy[1]; \
    memcpy(position_copy, position, sizeof(Position));

// restore board state
#define take_back() \
    memcpy(position, position_copy, sizeof(Position));
    
#endif