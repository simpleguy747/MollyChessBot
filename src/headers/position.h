#ifndef POSITION_H   /* Include guard */
#define POSITION_H

#include <stdint.h>

typedef struct Position {
    uint64_t type_of_pieces[7];
    uint64_t occupancy[2];
    int sideToMove;
    int  castling;
    uint64_t enpassantSquare;
    int halfMoves;
    int fullMoves;
} Position;

typedef struct Move{
    int move;
    int mvv_lva_value;
} Move;


#endif