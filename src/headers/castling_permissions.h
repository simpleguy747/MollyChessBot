#ifndef CASTLING_PERMISSIONS   /* Include guard */
#define CASTLING_PERMISSIONS

#include <stdint.h>

#define NO_CASTLING  0
#define WHITE_KINGSIDE_CASTLE 1
#define WHITE_QUEENSIDE_CASTLE 2
#define BLACK_KINGSIDE_CASTLE 4
#define BLACK_QUEENSIDE_CASTLE 8

extern const int CastleRightsConsts[64];
extern const uint64_t Castled_Rook_Files[2][2];
#endif