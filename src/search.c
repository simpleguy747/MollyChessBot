#include "search.h"
#include "position.h"
#include "movegen.h"
#include "display.h"
#include <stdio.h>
#include "move_manager.h"
#include "string.h"
#include "attack_manager.h"
#include "stdint.h"
#include "utilities.h"
#include "uci_helper.h"
#include "color.h"
#include <stdbool.h>
int best_move = -1;
uint64_t nodes = 0;
long long start_time = 0;
long long end_time = 0;
bool stop_search = false;

void CheckIfTimeOver()
{
    if (stop_search == false && (nodes & 1023) != 0)
    {
        long long current_time = GetCurrentTimeInMilliseconds();
        stop_search = current_time >= end_time ? true : false;
    }
}
int Negamax(Position *pos, int depth, int ply)
{
    CheckIfTimeOver();
    if (stop_search)
    {
        return 0;
    }
    if (depth == 0)
    {
        return 0;
    }
    nodes = nodes + 1;
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
            eval = -Negamax(pos, depth - 1, ply + 1);
        }
        take_back();
        if (stop_search)
        {
            break;
        }
        if (eval > max)
        {
            max = eval;
            if (ply == 0)
            {
                if (!stop_search)
                    best_move = moveList->moves[i].move;
            }
        }
    }

    if (movePlayed == 0)
    {
        return IsCheck(pos) ? (-MATE_VAL + ply) : 0;
    }

    return max;
}

void RootSearch(UCIHelper *uciHelper, Position *pos, int depth)
{
    int ply = 0;
    nodes = 0;
    int maxDepth = 50;

    int time = uciHelper->btime;
    int inc = uciHelper->binc;
    stop_search = false;
    start_time = GetCurrentTimeInMilliseconds();
    if (pos->sideToMove == COLOR_WHITE)
    {
        time = uciHelper->wtime;
        inc = uciHelper->winc;
    }
    if (time == 0 && inc == 0)
    {
        end_time = 100000000000;
    }
    end_time = start_time + (time / 20) + (inc / 2);
    char bestMoveStr[5];
    for (int d = 1; d <= maxDepth && !stop_search; d++)
    {

        long long t_start = GetCurrentTimeInMilliseconds();
        int eval = Negamax(pos, d, ply);
        long long t_end = GetCurrentTimeInMilliseconds();
        if (!stop_search)
        {
            MoveStrFromInt(best_move, bestMoveStr);
            printf("info depth %d nodes %ld score cp %d time %lld nps %lld pv %s\n", d, nodes, eval, (t_end - t_start), ((nodes * 1000) / (t_end - t_start + 1)), bestMoveStr);
        }
    }
    printf("bestmove %s\n", bestMoveStr);
}

// Move bestMove;
// int score = 0;

// ID loop while we have time
// {
//     Move moveBefore = bestMove;
//     int scoreThisIteration = search(depth);
//     if (searchStopped) bestMove = moveBefore;
// }

// return bestMove;