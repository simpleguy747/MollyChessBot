#ifndef MOVEGEN_H /* Include guard */
#define MOVEGEN_H

#include "position.h"

void GenerateMoves(Position *pos, MoveList *moveList);


#define SQ_TO(move) (move & 0x3F)
#define SQ_FROM(move) ((move>>6) & 0x3F)

#endif