#ifndef MOVEGEN_H /* Include guard */
#define MOVEGEN_H

#include "position.h"

void generate_moves(Position *pos, MoveList *moveList);
void generate_qsearch_moves(Position *pos, MoveList *moveList);

static inline int SQ_TO(int move)
{
    return move & 0x3F;
}

static inline int SQ_FROM(int move)
{
    return (move >> 6) & 0x3F;
}

static inline int TYPE_OF_MOVE(int move)
{
    return (move >> 12) & 0xF;
}

// #define SQ_TO(move) (move & 0x3F)
// #define SQ_FROM(move) ((move >> 6) & 0x3F)
// #define TYPE_OF_MOVE(move) ((move >> 12) & 0xF)

#endif