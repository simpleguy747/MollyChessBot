#include "attacks.h"
#include "gen_king_moves.h"
#include "gen_moves_base.h"
#include "pieces.h"
#include "utilities.h"
#include "castling_permissions.h"
#include "attack_manager.h"
#include <stdint.h>

void GenerateKingNonCastleMoves(const int us, const Position *pos, MoveList *moveList, const uint64_t targetBitboard, int typeOfMove)
{
    uint64_t ourKing = pos->type_of_pieces[KING] & pos->occupancy_by_color[us];
    for (; ourKing > 0; ourKing &= ourKing - 1)
    {
        int sqFrom = PopLSB(ourKing);
        uint64_t kingAttacksFromSquare = KING_ATTACKS[sqFrom] & targetBitboard;
        CreateMove(typeOfMove, sqFrom, kingAttacksFromSquare, moveList);
    }
}

void GenerateCastlingMoves(int sideToMove, uint64_t castlePermissions, uint64_t occupied, Position *position, MoveList *moveList)
{

    if ((castlePermissions & CastleBits[sideToMove][0]) && (!(occupied & CastleJump[sideToMove][0])) && (!IsSquareAttacked(CastleJumpSquares[sideToMove][0], position)) && (!IsSquareAttacked(CastleJumpSquares[sideToMove][1], position)))
    {
        moveList->moves[moveList->count].move = ENCODE_MOVE(MOVE_TYPE_CASTLE_QUEEN_SIDE, CastleSquares[sideToMove][0], CastleSquares[sideToMove][1]);
        moveList->count++;
    }

    if ((castlePermissions & CastleBits[sideToMove][1]) && (!(occupied & CastleJump[sideToMove][1])) && (!IsSquareAttacked(CastleJumpSquares[sideToMove][2], position)) && (!IsSquareAttacked(CastleJumpSquares[sideToMove][3], position)))
    {
        moveList->moves[moveList->count].move = ENCODE_MOVE(MOVE_TYPE_CASTLE_KING_SIDE, CastleSquares[sideToMove][2], CastleSquares[sideToMove][3]);
        moveList->count++;
    }
}
