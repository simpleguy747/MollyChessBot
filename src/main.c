#include <stdio.h>

#include "headers/fen_manager.h"
#include "headers/position.h"
int main()
{
  printf("Molly v1.0\n");
  Position pos[1];
  SetBoardFromFen("r1bqk2r/p4pp1/2pb1n1p/n3N3/3Pp3/8/PPP1BPPP/RNBQK2R b KQkq d3 0 11", pos);

  return 0;
}