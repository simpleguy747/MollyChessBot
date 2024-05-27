
#include "castling_permissions.h"
#include <stdint.h>

#define BlackQueensideRookBit 0x0100000000000000ULL
#define BlackKingsideRookBit 0x8000000000000000ULL
#define WhiteQueensideRookBit 0x0000000000000001ULL
#define WhiteKingsideRookBit 0x0000000000000080ULL

const int CastleRightsConsts[64] = {
    1, 0, 0, 0, 3, 0, 0, 2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    4, 0, 0, 0, 12, 0, 0, 8};

        const uint64_t Castled_Rook_Files[2][2] = {{
    0x00000000000000A0ULL, 0x9ULL}, {0xa000000000000000ULL,0x900000000000000ULL}};