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

int main()
{
  printf("Molly v1.0\n");
  // Position pos[1];
  // InitMagicsAll();
  // InitAll(pos);
  // SetBoardFromFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", pos);
  // DisplayBoard(pos);

  // MoveList moveList[1];
  // GenerateMoves(pos, moveList);

  // for (int i = 0; i < moveList->count; i++)
  // {
  //   int move = moveList->moves[i].move;
  //   DisplayMove(move);
  //   MakeMove(pos, move);
  // }

  // printf("Total moves : %d\n", moveList->count);

  // PerftNumbers("3rk2r/p4pQ1/3p2pb/1pp3P1/P2p4/2n2R1b/1PKN3P/2B4R w k - 0 1", 6,1017748582,1);
  //  PerftNumbers("3rk2r/p4pQ1/3p2pb/1pp3P1/P2p4/2n4R/1PKN3P/2B4R b k - 0 1", 5,1017748582,1);
  // PerftNumbers("3rk2r/p4pb1/3p2p1/1pp3P1/P2p4/2n4R/1PKN3P/2B4R w k - 0 2", 4, 1017748582, 1);
  //  PerftNumbers("3rk2R/p4pb1/3p2p1/1pp3P1/P2p4/2n5/1PKN3P/2B4R b - - 0 2", 3,1017748582,1);
  //  PerftNumbers("3rk2r/p4pQ1/3p2pb/1pp3P1/P2p4/2n2R1b/1PKN3P/2B4R w k - 0 1", 6,1017748582,1);

  TestPerft();

  return 0;
}