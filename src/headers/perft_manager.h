#ifndef PERFT_MANAGER_H /* Include guard */
#define PERFT_MANAGER_H
#include <stdint.h>
#include "position.h"

uint64_t perft(Position *pos, int depth, int ply);
void perft_numbers(char *fen, int depth, uint64_t expected_nodes, int index);
#endif