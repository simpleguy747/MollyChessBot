#ifndef GEN_MOVES_BASE_H /* Include guard */
#define GEN_MOVES_BASE_H

#include<stdint.h>
#include "position.h"

#define ENCODE_MOVE(moveType, from, to) ((moveType << 12) + ((from) << 6) + (to))

void CreateMoves(const int typeOfMove, const int sqFrom, uint64_t movesBitBoard, MoveList *moveList);

#endif