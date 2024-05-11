#ifndef POSITION_H /* Include guard */
#define POSITION_H

#include <stdint.h>

typedef struct Position
{
    uint64_t type_of_pieces[7];
    uint64_t occupancy_by_color[2];
    int board[64];
    int sideToMove;
    int castling;
    uint64_t enpassantSquare;
    int halfMoves;
    int fullMoves;
} Position;

typedef struct Move
{
    int move;
    int mvv_lva_value;
} Move;

typedef struct MoveList
{
    Move moves[256];
    int count;
} MoveList;


#define NO_CAP 0
#define CAP 1
#define ENPASSANT 2
#define KING_CASTLE 3
#define QUEEN_CASTLE 4
#define PROMOTION_KNIGHT 5
#define PROMOTION_BISHOP 6
#define PROMOTION_ROOK 7
#define PROMOTION_QUEEN 8

#endif