#ifndef GEN_KING_MOVES_H /* Include guard */
#define GEN_KING_MOVES_H

#include "position.h"
#include <stdint.h>
void generate_king_non_castle_moves(const int us, const Position *pos, MoveList *moveList, const uint64_t targetBitboard, int typeOfMove);
void generate_castling_moves(int sideToMove, uint64_t castlePermissions, uint64_t occupied, Position *position, MoveList *moveList);

#endif