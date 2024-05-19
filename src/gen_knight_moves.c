#include <stdint.h>
#include "gen_moves_base.h"
#include "gen_knight_moves.h"
#include "position.h"
#include "pieces.h"
#include "attacks.h"
#include "utilities.h"

void GenerateKnightMoves(const int us, const Position *pos, MoveList *moveList, const uint64_t targetBitboard, int typeOfMove)
{
    uint64_t ourKnights = pos->type_of_pieces[KNIGHT] & pos->occupancy_by_color[us];
    for (; ourKnights > 0; ourKnights &= ourKnights - 1)
    {
        int sqFrom = PopLSB(ourKnights);
        uint64_t knightAttacksFromSquare = KNIGHT_ATTACKS[sqFrom] & targetBitboard;
        CreateMoves(typeOfMove, sqFrom, knightAttacksFromSquare, moveList);
    }
}
