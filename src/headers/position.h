#ifndef POSITION_H /* Include guard */
#define POSITION_H

#include <stdint.h>

typedef struct Position
{
    uint64_t type_of_pieces[7];
    uint64_t occupancy_by_color[2];
    char board[64];
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


#define MOVE_TYPE_PAWN 0
#define MOVE_TYPE_KNIGHT 1
#define MOVE_TYPE_BISHOP 2
#define MOVE_TYPE_ROOK 3
#define MOVE_TYPE_QUEEN 4
#define MOVE_TYPE_KING 5
#define MOVE_TYPE_ENPASSANT 6
#define MOVE_TYPE_CASTLE_KING_SIDE 7
#define MOVE_TYPE_CASTLE_QUEEN_SIDE 8
#define MOVE_TYPE_PROMOTION_KNIGHT 9
#define MOVE_TYPE_PROMOTION_BISHOP 10
#define MOVE_TYPE_PROMOTION_ROOK 11
#define MOVE_TYPE_PROMOTION_QUEEN 12

#endif