#ifndef SEARCH_H /* Include guard */
#define SEARCH_H

#include "position.h"
#include "uci_helper.h"

extern uint64_t nodes;
void root_search(UCIHelper *uciHelper, Position *pos);

#define INF 100000
#define ALPHA -INF
#define BETA INF
#define MATE_VAL 9999
#define MATE_SCORE 9000

#endif
