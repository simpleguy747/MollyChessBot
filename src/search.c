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
#include "transposition_table.h"
#include "zobrist.h"
#include <inttypes.h>
#include <assert.h>

int best_move = -1;
uint64_t nodes = 0;
long long start_time = 0;
long long end_time = 0;
bool stop_search = false;

typedef struct LINE
{
    int cmove;        // Number of moves in the line.
    int argmove[256]; // The line.
} LINE;

void CheckIfTimeOver()
{
    if (stop_search == false && (nodes & 1023) != 0)
    {
        long long current_time = get_current_time_in_milliseconds();
        stop_search = current_time >= end_time ? true : false;
    }
}

void sort_moves(MoveList *moveList, int best_move_tt)
{
    for (int i = 0; i < moveList->count; i++)
    {
        if (moveList->moves[i].move == best_move_tt)
        {
            moveList->moves[i].mvv_lva_value += 9000000;
            break;
        }
    }
    // Sort moves by MVV/LVA score
    for (int i = 0; i < moveList->count; i++)
    {
        for (int j = i + 1; j < moveList->count; j++)
        {
            if (moveList->moves[i].mvv_lva_value < moveList->moves[j].mvv_lva_value)
            {
                Move temp = moveList->moves[i];
                moveList->moves[i] = moveList->moves[j];
                moveList->moves[j] = temp;
            }
        }
    }
}

// Quiescence Search
int QSearch(Position *pos, int ply, int alpha, int beta)
{
    int evaluation = evaluate(pos);

    if (evaluation >= beta)
    {
        return beta;
    }
    if (evaluation > alpha)
    {
        alpha = evaluation;
    }

    int eval;
    MoveList moveList[1];
    generate_qsearch_moves(pos, moveList);
    sort_moves(moveList,0);
    for (int i = 0; i < moveList->count; i++)
    {
        copy_board();

        make_move(pos, moveList->moves[i].move);

        if (!is_check(pos))
        {
            pos->sideToMove ^= 1;
            eval = -QSearch(pos, ply + 1, -beta, -alpha);

            if (eval > alpha)
            {
                if (eval >= beta)
                    return beta;
                alpha = eval;
            }
        }

        take_back();

        if (stop_search)
        {
            break;
        }
    }
    return alpha;
}

int is_repetition(uint64_t hash_key)
{
    for (int index = 0; index < repetition_index; index++)
    {
        if (RepetitionTable[index] == hash_key)
        {
            return 1;
        }
    }

    return 0;
}

int NegamaxAlphaBeta(Position *pos, int depth, int ply, int alpha, int beta, LINE *pline, int passed_depth)
{
    LINE line;
    line.cmove = 0;
    int best_move_tt = 0;
    int pvNode = beta - alpha > 1;
    if (depth == 0)
    {
        pline->cmove = 0;
        return QSearch(pos, ply + 1, alpha, beta);
    }
    nodes = nodes + 1;
    MoveList moveList[1];
    char movePlayed = 0;
    int eval;
    // Inclusion of hash table.

    int hash_flag = hashfALPHA;
    if (ply && is_repetition(pos->hash_key))
    {
        return 0;
    }
    HashEntry *hash_entry = read_hash_entry(pos->hash_key);

    if (ply && hash_entry && hash_entry->depth >= depth)
    {
        eval = hash_entry->eval;
        if (eval < -MATE_SCORE)
            eval += ply;
        if (eval > MATE_SCORE)
            eval -= ply;

        if (hash_entry->flag == hashfEXACT)
        {
            return eval;
        }
        if ((hash_entry->flag == hashfALPHA) && (eval <= alpha))
        {
            return alpha;
        }
        if ((hash_entry->flag == hashfBETA) && (eval >= beta))
        {
            return beta;
        }

        best_move_tt = hash_entry->move;
    }

    generate_moves(pos, moveList);
    sort_moves(moveList,best_move_tt);
    for (int i = 0; i < moveList->count; i++)
    {
        copy_board();
        int move = moveList->moves[i].move;
        make_move(pos, move);

        if (is_check(pos))
        {
            take_back();
            continue;
        }

        pos->sideToMove ^= 1;
        pos->hash_key ^= side_key;

        repetition_index++;
        RepetitionTable[repetition_index] = pos->hash_key;
        movePlayed = 1;

        eval = -NegamaxAlphaBeta(pos, depth - 1, ply + 1, -beta, -alpha, &line, passed_depth);
        repetition_index--;
        take_back();
        CheckIfTimeOver();
        if (stop_search)
        {
            pline->cmove = 0;
            return 0;
        }
        if (eval > alpha)
        {
            best_move_tt = move;
            alpha = eval;
            hash_flag = hashfEXACT;
            if (eval >= beta)
            {
                write_hash_entry(beta, depth, hashfBETA, pos->hash_key, ply, best_move_tt);
                return beta;
            }

            
            if (ply == 0)
            {
                if (!stop_search)
                    best_move = move;
            }

            pline->argmove[0] = move;
            memcpy(pline->argmove + 1, line.argmove, line.cmove * sizeof(int));
            pline->cmove = line.cmove + 1;
        }

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

    write_hash_entry(alpha, depth, hash_flag, pos->hash_key, ply, best_move_tt);
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
        // reset repetition index

        long long t_start = get_current_time_in_milliseconds();
        int eval = NegamaxAlphaBeta(pos, d, ply, -INF, INF, &pvLine, d);
        long long t_end = get_current_time_in_milliseconds();
        if (!stop_search)
        {
            move_str_from_int(best_move, bestMoveStr);
            printf("info depth %d nodes %ld score cp %d time %lld nps %lld", d, nodes, eval, (t_end - t_start), ((nodes * 1000) / (t_end - t_start + 1)));
            printf(" pv");
            for (int i = 0; i < pvLine.cmove; i++)
            {
                char moveStr[6];
                move_str_from_int(pvLine.argmove[i], moveStr); // Assuming you have a function to convert moves to string
                printf(" %s", moveStr);
            }
            printf("\n");
            fflush(stdout);
        }
    }
    printf("bestmove %s\n", bestMoveStr);
}
