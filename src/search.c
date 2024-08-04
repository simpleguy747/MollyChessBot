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
#include "eval.h"
#include <stdlib.h>

int best_move = -1;
uint64_t nodes = 0;
long long start_time = 0;
long long end_time = 0;
bool stop_search = false;

typedef struct LINE
{
    int cmove;       // Number of moves in the line.
    int argmove[32]; // The line.
} LINE;

void CheckIfTimeOver()
{
    if (stop_search == false && (nodes & 1023) != 0)
    {
        long long current_time = get_current_time_in_milliseconds();
        stop_search = current_time >= end_time ? true : false;
    }
}

int Negamax(Position *pos, int depth, int ply, LINE *pline)
{
    LINE line;
    CheckIfTimeOver();
    if (stop_search)
    {
        pline->cmove = 0;
        return evaluate(pos);
    }
    if (depth == 0)
    {
        pline->cmove = 0;
        return evaluate(pos);
    }
    nodes = nodes + 1;
    int max = -INF;
    int eval = max;
    MoveList moveList[1];
    char movePlayed = 0;
    generate_moves(pos, moveList);
    for (int i = 0; i < moveList->count; i++)
    {
        copy_board();
        make_move(pos, moveList->moves[i].move);
        if (!is_check(pos))
        {
            pos->sideToMove ^= 1;
            movePlayed = 1;
            eval = -Negamax(pos, depth - 1, ply + 1, &line);
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
            pline->argmove[0] = moveList->moves[i].move;
            memcpy(pline->argmove + 1, line.argmove, line.cmove * sizeof(int));
            pline->cmove = line.cmove + 1;
        }
    }

    if (movePlayed == 0)
    {
        pline->cmove = 0;
        return is_check(pos) ? (-MATE_VAL + ply) : 0;
    }

    return max;
}

int NegamaxAlphaBeta(Position *pos, int depth, int ply, int alpha, int beta, LINE *pline)
{
    // display_board(pos);
    LINE line;
    CheckIfTimeOver();
    if (stop_search)
    {
        pline->cmove = 0;
        return evaluate(pos);
    }
    if (depth == 0)
    {
        pline->cmove = 0;
        return evaluate(pos);
    }
    nodes = nodes + 1;
    MoveList moveList[1];
    char movePlayed = 0;
    int eval;
    generate_moves(pos, moveList);
    for (int i = 0; i < moveList->count; i++)
    {
        copy_board();
        make_move(pos, moveList->moves[i].move);
        // display_move( moveList->moves[i].move);
        if (!is_check(pos))
        {
            pos->sideToMove ^= 1;
            movePlayed = 1;
            eval = -NegamaxAlphaBeta(pos, depth - 1, ply + 1, -beta, -alpha, &line);
            if (eval > alpha)
            {
                if (eval >= beta)
                    return beta;
                alpha = eval;

                if (ply == 0)
                {
                    if (!stop_search)
                        best_move = moveList->moves[i].move;
                }
                pline->argmove[0] = moveList->moves[i].move;
                memcpy(pline->argmove + 1, line.argmove, line.cmove * sizeof(int));
                pline->cmove = line.cmove + 1;
            }
        }
        take_back();
        if (stop_search)
        {
            break;
        }
    }

    if (movePlayed == 0)
    {
        pline->cmove = 0;
        return is_check(pos) ? (-MATE_VAL + ply) : 0;
    }

    return alpha;
}

void root_search(UCIHelper *uciHelper, Position *pos)
{
    int ply = 0;
    nodes = 0;
    int maxDepth = 100;

    if (uciHelper->depth != 0)
    {
        maxDepth = uciHelper->depth;
    }
    int time = uciHelper->btime;
    int inc = uciHelper->binc;
    stop_search = false;
    start_time = get_current_time_in_milliseconds();
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
    char bestMoveStr[6];

    for (int d = 1; d <= maxDepth && !stop_search; d++)
    {
        LINE pvLine;
        pvLine.cmove = 0;
        nodes = 0;
        long long t_start = get_current_time_in_milliseconds();
        int eval = NegamaxAlphaBeta(pos, d, ply, -INF, INF, &pvLine);
        // int eval = Negamax(pos, d, ply, &pvLine);
        long long t_end = get_current_time_in_milliseconds();
        if (!stop_search)
        {
            move_str_from_int(best_move, bestMoveStr);
            printf("info depth %d nodes %ld score cp %d time %lld nps %lld", d, nodes, eval, (t_end - t_start), ((nodes * 1000) / (t_end - t_start + 1)));
            printf(" pv ");
            for (int i = 0; i < pvLine.cmove; i++)
            {
                char moveStr[6];
                move_str_from_int(pvLine.argmove[i], moveStr); // Assuming you have a function to convert moves to string
                printf("%s ", moveStr);
            }
            printf("\n");
            fflush(stdout);
        }
    }
    printf("bestmove %s\n", bestMoveStr);
}

int randoms(int lower, int upper)
{
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

void root_search2(UCIHelper *uciHelper, Position *pos, int depth)
{
    MoveList moveList[1];

    int bestMove = -1;
    char movePlayed = 0;
    generate_moves(pos, moveList);
    int eval = -INF;
    for (int i = 0; i < moveList->count; i++)
    {
        int index = randoms(0, moveList->count - 1);
        // printf("random index :: %d\n", index);
        copy_board();
        make_move(pos, moveList->moves[index].move);
        if (!is_check(pos))
        {
            pos->sideToMove ^= 1;
            bestMove = moveList->moves[index].move;
            eval = evaluate(pos);
            movePlayed = 1;
            break;
        }
        take_back();
    }

    if (movePlayed == 0)
    {
        for (int i = 0; i < moveList->count; i++)
        {
            copy_board();
            make_move(pos, moveList->moves[i].move);
            if (!is_check(pos))
            {
                pos->sideToMove ^= 1;
                bestMove = moveList->moves[i].move;
                eval = evaluate(pos);
                movePlayed = 1;
                break;
            }
            take_back();
        }
    }

    char bestMoveStr[6];
    move_str_from_int(bestMove, bestMoveStr);
    printf("info depth %d nodes %d score cp %d time %d nps %d pv %s\n", 1, 1, eval, 100, 100000, bestMoveStr);
    printf("bestmove %s\n", bestMoveStr);
    fflush(stdout);
}