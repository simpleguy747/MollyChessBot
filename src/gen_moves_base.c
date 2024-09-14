#include "gen_moves_base.h"
#include "position.h"
#include "utilities.h"
#include "mvvlva.h"

static evil_create_move = 0;
void create_move(const Position *pos, const int typeOfMove, const int sqFrom, uint64_t movesBitBoard, MoveList *moveList)
{
    for (; movesBitBoard > 0; movesBitBoard &= movesBitBoard - 1)
    {
        // evil_create_move = evil_create_move + 1;
        // printf("evil_create_move %d\n",evil_create_move);
        int sqTo = PopLSB(movesBitBoard);
        moveList->moves[moveList->count].move = ENCODE_MOVE(typeOfMove, sqFrom, sqTo);
        calculate_mvv_lva(pos, &moveList->moves[moveList->count]);
        moveList->count++;
        
    }
}