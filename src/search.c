#include "search.h"
#include "position.h"
#include "movegen.h"
#include "display.h"
#include <stdio.h>
#include "move_manager.h"
#include "string.h"
#include "attack_manager.h"

int Search(Position *pos, int depth, int ply)
{
    if (depth == 0)
    {
        return 0;
    }

    int max = -INF;
    int eval = max;
    MoveList moveList[1];
    char movePlayed = 0;
    GenerateMoves(pos, moveList);
    for (int i = 0; i < moveList->count; i++)
    {
        copy_board();
        MakeMove(pos, moveList->moves[i].move);
        if (!IsCheck(pos))
        {
            pos->sideToMove ^= 1;
            movePlayed = 1;
            eval = -Search(pos, depth - 1, ply + 1);
        }
        take_back();

        if (eval > max)
        {
            max = eval;
        }
    }

    if (movePlayed == 0)
    {
        return IsCheck(pos) ? (-MATE_VAL + ply) : 0;
    }

    return max;
}
int RootSearch(Position *pos, int depth)
{
    int max = -INF;
    int eval = max;
    int bestMove = -1;
    int ply = 0;
    MoveList moveList[1];
    char movePlayed = 0;
    GenerateMoves(pos, moveList);
    for (int i = 0; i < moveList->count; i++)
    {
        copy_board();
        MakeMove(pos, moveList->moves[i].move);
        if (!IsCheck(pos))
        {
            pos->sideToMove ^= 1;
            movePlayed = 1;
            eval = -Search(pos, depth - 1, ply + 1);
        }
        take_back();

        if (eval > max)
        {
            max = eval;
            bestMove = moveList->moves[i].move;
        }
    }

    DisplayMove(bestMove);
    printf("eval %d\n", max);
    if (movePlayed == 0)
    {
        return IsCheck(pos) ? (-MATE_VAL) : 0;
    }

    return max;
}