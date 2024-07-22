#ifndef GEN_PAWN_MOVES_H /* Include guard */
#define GEN_PAWN_MOVES_H

#include "position.h"
#include <stdint.h>

void generate_pawn_captures_and_promotions(const int us, const Position *pos, MoveList *moveList, const uint64_t targetBitboard, int forwardDirection);
void generate_pawn_non_captures_and_promotions(const int us, const Position *pos, MoveList *moveList, const uint64_t targetBitboard, int forwardDirection);


#endif