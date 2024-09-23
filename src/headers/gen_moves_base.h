#ifndef GEN_MOVES_BASE_H /* Include guard */
#define GEN_MOVES_BASE_H

#include "position.h"
#include <stdint.h>

// #define ENCODE_MOVE(moveType, from, to) ((moveType << 12) + ((from) << 6) + (to))

static inline int ENCODE_MOVE(int moveType, int from, int to)
{
    return (moveType << 12) + (from << 6) + to;
}

void create_move(const Position *pos, const int typeOfMove, const int sqFrom, uint64_t movesBitBoard, MoveList *moveList);

#endif
