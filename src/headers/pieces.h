#ifndef PIECES_H /* Include guard */
#define PIECES_H

#include "color.h"

// https://www.chessprogramming.org/Pieces#Piece-Type_Coding

// Piece types.
#define EMPTY 0
#define PAWN 1
#define KNIGHT 2
#define BISHOP 3
#define ROOK 4
#define QUEEN 5
#define KING 6

// Pieces. // piecetype + 8*color
#define WP 1
#define WN 2
#define WB 3
#define WR 4
#define WQ 5
#define WK 6

#define BP 9
#define BN 10
#define BB 11
#define BR 12
#define BQ 13
#define BK 14

#define PIECES_STR ".PNBRQK#*pnbrqk"

static inline int TYPE_OF_PIECE(int piece)
{
    return piece & 7;
}

static inline int COLOR_OF_PIECE(int piece)
{
    return piece >> 3;
}

static inline int MAKE_PIECE(int type, int color)
{
    return type+(color<<3);
}



// #define TYPE_OF_PIECE(piece) ((piece)&7)
// #define COLOR_OF_PIECE(piece) ((piece)>>3)
// #define MAKE_PIECE(type,color) ((type)+(color<<3))
#endif
