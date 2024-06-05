#include <stdio.h>
#include <assert.h>
#include "fen_manager.h"
#include "position.h"
#include "display.h"
#include "movegen.h"
#include "init.h"
#include "magic_bitboards.h"
#include "move_manager.h"
#include "perft_manager.h"
#include <sys/time.h>
#include "tests/perft_tests.h"
#include "search.h"
int main()
{
  printf("Molly v1.0\n");
  Position pos[1];
  InitMagicsAll();
  InitAll(pos);
  SetBoardFromFen("r1b3k1/pppn3p/3p2rb/3P1K2/2P1P3/2N2P2/PP1QB3/R4R2 b - - 0 1", pos);
  DisplayBoard(pos);
  int eval = RootSearch(pos, 2);
  // MoveList moveList[1];
  // GenerateMoves(pos, moveList);

  // for (int i = 0; i < moveList->count; i++)
  // {
  //   int move = moveList->moves[i].move;
  //   DisplayMove(move);
  //   MakeMove(pos, move);
  // }

  // printf("Total moves : %d\n", moveList->count);

  // PerftNumbers("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", 6,119060324,1);

  // TestPerft();

  return 0;
}