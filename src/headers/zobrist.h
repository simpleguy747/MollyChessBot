#ifndef ZOBRIST_H /* Include guard */
#define ZOBRIST_H

#include <stdint.h>
#include "position.h"

extern uint64_t piece_keys[15][64];
extern uint64_t enpassant_keys[64];
extern uint64_t castle_keys[16];
extern uint64_t side_key;

void init_random_hash_keys();
uint64_t generate_hash_key_from_scratch(Position* pos);
#endif
