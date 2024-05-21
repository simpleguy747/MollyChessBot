#include "attacks.h"
#include "gen_king_moves.h"
#include "gen_moves_base.h"
#include "pieces.h"
#include "utilities.h"
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
