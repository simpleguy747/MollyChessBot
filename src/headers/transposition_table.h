#ifndef TRANSPOSITION_TABLE_H /* Include guard */
#define TRANSPOSITION_TABLE_H

#include <stdint.h>
#include "position.h"

#define HASH_SIZE 4194304 // 4MB Will set this dynamic later.

#define hashfEXACT 0
#define hashfALPHA 1
#define hashfBETA 2
#define NO_HASH_FOUND -1

typedef struct HashEntry
{

    uint64_t key;
    int8_t depth;
    int8_t flag;
    int eval;
} HashEntry;

extern HashEntry tt[HASH_SIZE];

void clear_hash_table();
int read_hash_entry(int depth, int alpha, int beta, uint64_t hash_key);
void write_hash_entry(int eval, int depth, int hash_flag, uint64_t hash_key);

#endif