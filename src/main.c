#include <stdio.h>

#include "fen_manager.h"
#include "position.h"
#include "display.h"
#include "movegen.h"
#include "init.h"
#include "magic_bitboards.h"

int main()
{
  printf("Molly v1.0\n");
  Position pos[1];
  InitMagicsAll();
  InitAll(pos);
  SetBoardFromFen("rnbqkbnr/1pp1ppp1/p2p3p/8/3PP2P/8/PPP2PP1/RNBQKBNR w KQkq - 0 4", pos);
  DisplayBoard(pos);

  MoveList moveList[1];
  GenerateMoves(pos, moveList);

  for (int i = 0; i < moveList->count; i++)
  {
    DisplayMove(moveList->moves[i].move);
  }

  printf("Total moves : %d\n", moveList->count);
  
  return 0;
}