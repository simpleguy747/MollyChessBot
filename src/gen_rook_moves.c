#include "attacks.h"
#include "gen_moves_base.h"
#include "gen_rook_moves.h"
#include "pieces.h"
#include "position.h"
#include "utilities.h"
#include <stdint.h>

void generate_rook_moves(const int us, const Position *pos, MoveList *moveList, const uint64_t targetBitboard, uint64_t occupied, int typeOfMove)
{
    uint64_t ourRooks = (pos->type_of_pieces[ROOK]) & pos->occupancy_by_color[us];

    for (; ourRooks > 0; ourRooks &= ourRooks - 1)
    {
        int sqFrom = PopLSB(ourRooks);
        uint64_t rookAttacksFromSquare = generate_rook_attacks(sqFrom, occupied) & targetBitboard;
        create_move(pos,typeOfMove, sqFrom, rookAttacksFromSquare, moveList);
    }
}
