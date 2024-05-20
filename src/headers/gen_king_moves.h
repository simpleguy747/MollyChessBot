#ifndef GEN_KING_MOVES_H /* Include guard */
#define GEN_KING_MOVES_H

#include "position.h"
#include <stdint.h>

void GenerateKingNonCastleMoves(const int us, const Position *pos, MoveList *moveList, const uint64_t targetBitboard, int typeOfMove);

#endif