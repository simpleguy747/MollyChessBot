#include <stdio.h>

#include "headers/fen_manager.h"
#include "headers/position.h"
#include "display.h"
#include "movegen.h"
int main()
{
  printf("Molly v1.0\n");
  Position pos[1];
  SetBoardFromFen("3r1r1k/4P2p/1p3p1p/P1pP2P1/8/2P5/4P3/K7 w - c6 0 1", pos);
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