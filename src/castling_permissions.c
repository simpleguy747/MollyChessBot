
#include "castling_permissions.h"
#include "squares.h"
#include <stdint.h>

#define BlackQueensideRookBit 0x0100000000000000ULL
#define BlackKingsideRookBit 0x8000000000000000ULL
#define WhiteQueensideRookBit 0x0000000000000001ULL
#define WhiteKingsideRookBit 0x0000000000000080ULL

const int Castle_Rights_Consts[64] = {
    WHITE_QUEENSIDE_CASTLE, 0, 0, 0, 3, 0, 0, WHITE_KINGSIDE_CASTLE,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    BLACK_QUEENSIDE_CASTLE, 0, 0, 0, 12, 0, 0, BLACK_KINGSIDE_CASTLE};

const uint64_t Castled_Rook_Files[2][2] = {{0x00000000000000A0ULL, 0x9ULL}, {0xa000000000000000ULL, 0x900000000000000ULL}};

const int Castled_Rook_Squares[2][4] = {{SQ_A1, SQ_D1, SQ_H1, SQ_F1}, {SQ_A8, SQ_D8, SQ_H8, SQ_F8}};

const uint64_t CastleBits[2][2] = {{WHITE_QUEENSIDE_CASTLE, WHITE_KINGSIDE_CASTLE}, {BLACK_QUEENSIDE_CASTLE, BLACK_KINGSIDE_CASTLE}};
const uint64_t Castle_Jump[2][2] = {{0xeULL, 0x60ULL}, {0xe00000000000000ULL, 0x6000000000000000ULL}};
const int Castle_Jump_Squares[2][4] = {{SQ_E1, SQ_D1, SQ_E1, SQ_F1}, {SQ_E8, SQ_D8, SQ_E8, SQ_F8}};
const int Castle_Squares[2][4] = {{SQ_E1, SQ_C1, SQ_E1, SQ_G1}, {SQ_E8, SQ_C8, SQ_E8, SQ_G8}};