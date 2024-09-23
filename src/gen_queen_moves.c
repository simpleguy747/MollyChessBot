#include "attacks.h"
#include "gen_moves_base.h"
#include "gen_queen_moves.h"
#include "pieces.h"
#include "position.h"
#include "utilities.h"
#include <stdint.h>

void generate_queen_moves(const int us, const Position *pos, MoveList *moveList, const uint64_t targetBitboard, uint64_t occupied, int typeOfMove)
{
    uint64_t ourQueens = pos->type_of_pieces[QUEEN] & pos->occupancy_by_color[us];

    for (; ourQueens > 0; ourQueens &= ourQueens - 1)
    {
        int sqFrom = PopLSB(ourQueens);
        uint64_t queenAttacksFromSquare = (generate_rook_attacks(sqFrom, occupied) | generate_bishop_attacks(sqFrom, occupied)) & targetBitboard;
        create_move(pos,typeOfMove, sqFrom, queenAttacksFromSquare, moveList);
    }
}
