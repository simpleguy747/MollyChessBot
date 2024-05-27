#include <stdio.h>

#include "fen_manager.h"
#include "position.h"
#include "display.h"
#include "movegen.h"
#include "init.h"
#include "magic_bitboards.h"
#include "move_manager.h"

int main()
{
  printf("Molly v1.0\n");
  Position pos[1];
  InitMagicsAll();
  InitAll(pos);
  SetBoardFromFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", pos);
  DisplayBoard(pos);

  MoveList moveList[1];
  GenerateMoves(pos, moveList);

  for (int i = 0; i < moveList->count; i++)
  {
    int move = moveList->moves[i].move;
    DisplayMove(move);
    MakeMove(pos,move);
  }

  printf("Total moves : %d\n", moveList->count);
  
  return 0;
}