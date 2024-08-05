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
#include "uci_helper.h"
int main()
{
  //uci_loop();
  // perft_numbers("r2qkb1r/pp2nppp/3p4/2pNN1B1/2BnP3/3P4/PPP2PPP/R2bK2R w KQkq - 1 1",6,500,1);
  Position pos;
  MoveList moveList;
   init_magics_all();
  init_all(&pos);
  set_board_from_fen("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1",&pos);
  generate_moves(&pos,&moveList);
  for(int i=0;i<moveList.count;i++){

    display_move_and_nodes(moveList.moves[i].move,moveList.moves[i].mvv_lva_value);
  }
  return 0;
}