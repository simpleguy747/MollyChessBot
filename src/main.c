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
#include "tuner.h"
int main()
{
  //tune();
    uci_loop();
  // display_move(593);
  // display_move(3299);
  // Position pos[1];
  // init_all(pos);
  // init_magics_all();

  // set_board_from_fen("r1b1kb1N/pppnq1pB/8/8/3Pp3/8/PPPK2PP/RNB5 w q - 0 12", pos);
  // // set_board_from_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", pos);
  
  // UCIHelper uciHelper[1];

  // uciHelper->wtime = 300000000;
  // uciHelper->btime = 300000000;
  // uciHelper->winc = 100000;
  // uciHelper->binc = 100000;
  // uciHelper->depth = 0;

  // clear_hash_table();

  // root_search(uciHelper, pos);

  return 0;
}