#include "attack_manager.h"
#include <stdint.h>
#include "position.h"
#include "pieces.h"
#include "attacks.h"
#include "squares.h"
#include "utilities.h"

uint64_t is_square_attacked(int square, Position *pos)
{
    const int us = pos->sideToMove;
    const int enemy = us ^ 1;
    const uint64_t occupied = ~pos->type_of_pieces[EMPTY];
    uint64_t pieces = pos->occupancy_by_color[enemy] & pos->type_of_pieces[KNIGHT];

    if (pieces & KNIGHT_ATTACKS[square])
        return 1;

    pieces = pos->occupancy_by_color[enemy] & pos->type_of_pieces[KING];
    if (pieces & KING_ATTACKS[square])
        return 1;

    pieces = pos->occupancy_by_color[enemy] & (pos->type_of_pieces[BISHOP] | pos->type_of_pieces[QUEEN]);
    if (pieces & generate_bishop_attacks(square, occupied))
        return 1;

    pieces = pos->occupancy_by_color[enemy] & (pos->type_of_pieces[ROOK] | pos->type_of_pieces[QUEEN]);
    if (pieces & generate_rook_attacks(square, occupied))
        return 1;

    pieces = (((pos->occupancy_by_color[enemy] & pos->type_of_pieces[PAWN] & NOT_FILE_A_BB) << 7) >> (16 * enemy)) | (((pos->occupancy_by_color[enemy] & pos->type_of_pieces[PAWN] & NOT_FILE_H_BB) << 9) >> (16 * enemy));

    return pieces & (1ULL << square);
}

uint64_t is_check(Position *pos)
{
    int kingSquare = PopLSB(pos->type_of_pieces[KING] & pos->occupancy_by_color[pos->sideToMove]);
    uint64_t isAttacked = is_square_attacked(kingSquare, pos);
    return isAttacked;
}