#ifndef POSITION_H   /* Include guard */
#define POSITION_H

#include <stdint.h>

typedef struct Position {
    uint64_t pieces[15];
    uint64_t occupancy[2];
    int sideToMove;
    int  castling;
    uint64_t enpassantSquare;
    int halfMoves;
    int fullMoves;
} Position;


#endif