#ifndef SEARCH_H /* Include guard */
#define SEARCH_H

#include "position.h"

int RootSearch(Position *pos, int depth);

#define INF 100000
#define ALPHA -INF
#define BETA INF
#define MATE_VAL 9999

#endif