#include "attacks.h"
#include "gen_king_moves.h"
#include "gen_moves_base.h"
#include "pieces.h"
#include "utilities.h"
#include "castling_permissions.h"
#include "attack_manager.h"
#include <stdint.h>

void generate_king_non_castle_moves(const int us, const Position *pos, MoveList *moveList, const uint64_t targetBitboard, int typeOfMove)
{
    uint64_t ourKing = pos->type_of_pieces[KING] & pos->occupancy_by_color[us];
    for (; ourKing > 0; ourKing &= ourKing - 1)
    {
        int sqFrom = PopLSB(ourKing);
        uint64_t kingAttacksFromSquare = KING_ATTACKS[sqFrom] & targetBitboard;
        create_move(typeOfMove, sqFrom, kingAttacksFromSquare, moveList);
    }
}

void generate_castling_moves(int sideToMove, uint64_t castlePermissions, uint64_t occupied, const Position *position, MoveList *moveList)
{

    if ((castlePermissions & CastleBits[sideToMove][0]) && (!(occupied & Castle_Jump[sideToMove][0])) && (!is_square_attacked(Castle_Jump_Squares[sideToMove][0], position)) && (!is_square_attacked(Castle_Jump_Squares[sideToMove][1], position)))
    {
        moveList->moves[moveList->count].move = ENCODE_MOVE(MOVE_TYPE_CASTLE_QUEEN_SIDE, Castle_Squares[sideToMove][0], Castle_Squares[sideToMove][1]);
        moveList->count++;
    }

    if ((castlePermissions & CastleBits[sideToMove][1]) && (!(occupied & Castle_Jump[sideToMove][1])) && (!is_square_attacked(Castle_Jump_Squares[sideToMove][2], position)) && (!is_square_attacked(Castle_Jump_Squares[sideToMove][3], position)))
    {
        moveList->moves[moveList->count].move = ENCODE_MOVE(MOVE_TYPE_CASTLE_KING_SIDE, Castle_Squares[sideToMove][2], Castle_Squares[sideToMove][3]);
        moveList->count++;
    }
}
