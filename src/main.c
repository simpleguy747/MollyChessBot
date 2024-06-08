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
  UciLoop();
  return 0;
}