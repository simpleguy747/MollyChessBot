#include "transposition_table.h"
#include <string.h>
#include "search.h"

HashEntry tt[HASH_SIZE];
uint64_t RepetitionTable[1024];
int repetition_index = 0;
void clear_hash_table()
{
    // Assuming HASH_SIZE is a defined constant
    memset(tt, 0, sizeof(HashEntry) * HASH_SIZE);
}

HashEntry *read_hash_entry(uint64_t hash_key)
{
    int hash_index = hash_key % HASH_SIZE;
    HashEntry *hash_entry = &tt[hash_index];

    if (hash_entry->key == hash_key)
    {
        return hash_entry;
    }

    return NULL;
}

void write_hash_entry(int eval, int depth, int hash_flag, uint64_t hash_key, int ply)
{
    int hash_index = hash_key % HASH_SIZE;
    HashEntry *hash_entry = &tt[hash_index];

    if (eval < -MATE_SCORE)
        eval -= ply;
    if (eval > MATE_SCORE)
        eval += ply;

    hash_entry->key = hash_key;
    // hash_entry->hash_move = move;
    hash_entry->eval = eval;
    hash_entry->depth = depth;
    hash_entry->flag = hash_flag;
}
