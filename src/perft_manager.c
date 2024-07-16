#include "perft_manager.h"
#include "position.h"
#include <stdint.h>
#include "movegen.h"
#include "move_manager.h"
#include "string.h"
#include "attack_manager.h"
#include "display.h"
#include <sys/time.h>
#include <assert.h>
#include <stdio.h>
#include "magic_bitboards.h"
#include "fen_manager.h"
#include "init.h"

uint64_t Divide3(Position *pos, int depth, int ply)
{
    uint64_t nodes = 0;
    if (depth == 0)
    {
        return 1;
    }

    MoveList moveList[1];
    generate_moves(pos, moveList);
    for (int i = 0; i < moveList->count; i++)
    {
        uint64_t nodes_divide = 0;
        copy_board();
        // PrintPosition(position);
        make_move(pos, moveList->moves[i].move);
       // display_board(pos);
        if (!is_check(pos))
        {
            pos->sideToMove ^= 1;
            nodes_divide = Divide3(pos, depth - 1, ply + 1);
            nodes += nodes_divide;
            // if(depth > 6)
            //display_move_and_nodes(moveList->moves[i].move, nodes_divide);
        }
        take_back();
    }

    return nodes;
}

uint64_t Divide2(Position *pos, int depth, int ply)
{
    uint64_t nodes = 0;
    if (depth == 0)
    {
        return 1;
    }

    MoveList moveList[1];
    generate_moves(pos, moveList);
    for (int i = 0; i < moveList->count; i++)
    {
        uint64_t nodes_divide = 0;
        copy_board();
        // PrintPosition(position);
        make_move(pos, moveList->moves[i].move);
       // display_board(pos);
        if (!is_check(pos))
        {
            pos->sideToMove ^= 1;
            nodes_divide = Divide3(pos, depth - 1, ply + 1);
            nodes += nodes_divide;
            // if(depth > 6)
            display_move_and_nodes(moveList->moves[i].move, nodes_divide);
        }
        take_back();
    }

    return nodes;
}

uint64_t Divide1(Position *pos, int depth, int ply)
{
    uint64_t nodes = 0;
    if (depth == 0)
    {
        return 1;
    }

    MoveList moveList[1];
    generate_moves(pos, moveList);
    for (int i = 0; i < moveList->count; i++)
    {
        uint64_t nodes_divide = 0;
        copy_board();
        // PrintPosition(position);
        make_move(pos, moveList->moves[i].move);
       // display_board(pos);
        if (!is_check(pos))
        {
            pos->sideToMove ^= 1;
            nodes_divide = Divide2(pos, depth - 1, ply + 1);
            nodes += nodes_divide;
            // if(depth > 6)
            display_move_and_nodes(moveList->moves[i].move, nodes_divide);
        }
        take_back();
    }

    return nodes;
}

uint64_t Divide(Position *pos, int depth, int ply)
{
    uint64_t nodes = 0;
    if (depth == 0)
    {
        return 1;
    }

    MoveList moveList[1];
    generate_moves(pos, moveList);
    for (int i = 0; i < moveList->count; i++)
    {
        uint64_t nodes_divide = 0;
        copy_board();
        // PrintPosition(position);
        make_move(pos, moveList->moves[i].move);
       // display_board(pos);
        if (!is_check(pos))
        {
            pos->sideToMove ^= 1;
            nodes_divide = Divide1(pos, depth - 1, ply + 1);
            nodes += nodes_divide;
            display_move_and_nodes(moveList->moves[i].move, nodes_divide);
        }
        take_back();
    }

    return nodes;
}

uint64_t perft(Position *pos, int depth, int ply)
{
    uint64_t nodes = 0;
    if (depth == 0)
    {
        return 1;
    }

    MoveList moveList[1];
    generate_moves(pos, moveList);
    for (int i = 0; i < moveList->count; i++)
    {
        uint64_t nodes_divide = 0;
        copy_board();
        // PrintPosition(position);
        make_move(pos, moveList->moves[i].move);
       // display_board(pos);
        if (!is_check(pos))
        {
            pos->sideToMove ^= 1;
            nodes_divide = perft(pos, depth - 1, ply + 1);
            nodes += nodes_divide;
          //   display_move_and_nodes(moveList->moves[i].move, nodes_divide);
            // printf("%ld\n",nodes_divide);
        }
        take_back();
    }

    return nodes;
}


long long get_current_time_in_milliseconds1()
{
  struct timeval currentTime;
  gettimeofday(&currentTime, NULL);
  return currentTime.tv_sec * 1000LL + currentTime.tv_usec / 1000LL;
}

void perft_numbers(char *fen, int depth, uint64_t expected_nodes, int index)
{
  Position pos[1];
  init_magics_all();
  init_all(pos);
  set_board_from_fen(fen, pos);
  long long t0 = get_current_time_in_milliseconds1();
  uint64_t nodes = perft(pos, depth, 0);
  long long t1 = get_current_time_in_milliseconds1();
  printf("%d. fen: %s depth: %d actual nodes: %ld expected nodes: %ld time_taken: %lldms speed %f Mnps\n", index,fen,depth,nodes,expected_nodes, (t1 - t0), ((1.0 * nodes) / ((t1 - t0)*1000+1)));
//   assert(expected_nodes == nodes);
}