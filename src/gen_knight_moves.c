#include "attacks.h"
#include "gen_knight_moves.h"
#include "gen_moves_base.h"
#include "pieces.h"
#include "position.h"
#include "utilities.h"
#include <stdint.h>

void GenerateKnightMoves(const int us, const Position *pos, MoveList *moveList, const uint64_t targetBitboard, int typeOfMove)
{
    uint64_t ourKnights = pos->type_of_pieces[KNIGHT] & pos->occupancy_by_color[us];
    for (; ourKnights > 0; ourKnights &= ourKnights - 1)
    {
        int sqFrom = PopLSB(ourKnights);
        uint64_t knightAttacksFromSquare = KNIGHT_ATTACKS[sqFrom] & targetBitboard;
        CreateMove(typeOfMove, sqFrom, knightAttacksFromSquare, moveList);
    }
}
