#include "gen_moves_base.h"

#include "position.h"
#include "utilities.h"

void CreateMoves(const int typeOfMove, const int sqFrom, uint64_t movesBitBoard, MoveList *moveList)
{
    for (; movesBitBoard > 0; movesBitBoard &= movesBitBoard - 1)
    {
        int sqTo = PopLSB(movesBitBoard);
        moveList->moves[moveList->count].move = ENCODE_MOVE(typeOfMove, sqFrom, sqTo);
        moveList->count++;
    }
}