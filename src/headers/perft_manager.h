#ifndef PERFT_MANAGER_H /* Include guard */
#define PERFT_MANAGER_H
#include <stdint.h>
#include "position.h"

uint64_t Perft(Position *pos, int depth, int ply);
void PerftNumbers(char *fen, int depth, uint64_t expected_nodes, int index);
#endif