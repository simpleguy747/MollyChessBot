#include "attacks.h"
#include "gen_bishop_moves.h"
#include "gen_moves_base.h"
#include "pieces.h"
#include "position.h"
#include "utilities.h"
#include <stdint.h>

void GenerateBishopAndQueenMoves(const int us, const Position *pos, MoveList *moveList, const uint64_t targetBitboard, uint64_t occupied, int typeOfMove)
{
    uint64_t ourBishops = (pos->type_of_pieces[BISHOP]|pos->type_of_pieces[QUEEN]) & pos->occupancy_by_color[us];
    
    for (; ourBishops > 0; ourBishops &= ourBishops - 1)
    {
        int sqFrom = PopLSB(ourBishops);
        uint64_t bishopAttacksFromSquare = GenerateBishopAttacks(sqFrom, occupied) & targetBitboard;
        CreateMove(typeOfMove, sqFrom, bishopAttacksFromSquare, moveList);
    }
}