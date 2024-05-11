#ifndef GEN_PAWN_MOVES_H /* Include guard */
#define GEN_PAWN_MOVES_H

#include "position.h"
#include <stdint.h>

void GeneratePawnMoves(const int us, const Position *pos, MoveList *moveList, const uint64_t emptyBitboard, uint64_t enemyBitboard, int forwardDirection);


#endif