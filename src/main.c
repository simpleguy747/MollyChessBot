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
#include "prng.h"
#include <inttypes.h>
#include "zobrist.h"
#include "pieces.h"
#include "squares.h"
#include "perft_manager.h"
#include "transposition_table.h"
int main()
{
  // uci_loop();

  Position pos[1];
  init_all(pos);
  init_magics_all();

  set_board_from_fen("8/k7/3p4/p2P1p2/P2P1P2/8/8/K7 w - - 0 1", pos);
  UCIHelper uciHelper[1];

  uciHelper->wtime = 300000000;
  uciHelper->btime = 300000000;
  uciHelper->winc = 100000;
  uciHelper->binc = 100000;
  uciHelper->depth = 0;

  clear_hash_table();

  root_search(uciHelper, pos);

  return 0;
}