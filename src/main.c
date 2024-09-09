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

int main()
{
  // uci_loop();
  test_perft();

  // perft_numbers("4r3/5b2/p3Pn2/P1kP4/2p4p/7N/2BK2P1/3N2R1 w - - 0 1", 2, 28, 7);
  return 0;
}