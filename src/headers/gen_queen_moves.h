#ifndef GEN_QUEEN_MOVES_H
#define GEN_QUEEN_MOVES_H

#include "position.h"
#include <stdint.h>

void generate_queen_moves(const int us, const Position *pos, MoveList *moveList, const uint64_t targetBitboard, uint64_t occupied, int typeOfMove);


#endif