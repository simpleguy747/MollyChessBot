#ifndef GEN_KNIGHT_MOVES_H /* Include guard */
#define GEN_KNIGHT_MOVES_H

#include "position.h"
#include <stdint.h>
void generate_knight_moves(const int us, const Position *pos, MoveList *moveList, const uint64_t targetBitboard, int typeOfMove);

#endif
