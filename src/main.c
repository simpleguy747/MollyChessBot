#include <stdio.h>

#include "headers/fen_manager.h"
#include "headers/position.h"
#include "display.h"
#include "movegen.h"
int main()
{
  printf("Molly v1.0\n");
  Position pos[1];
  SetBoardFromFen("rnbqkbnr/pppppppp/8/8/4K3/8/PPPPPPPP/RNBQ1BNR w kq - 0 1", pos);
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