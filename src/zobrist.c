#include "zobrist.h"
#include "pieces.h"
#include "squares.h"
#include "prng.h"
#include "position.h"
#include "squares.h"
#include "utilities.h"
#include "inttypes.h"
#include <stdio.h>

uint64_t piece_keys[15][64];
uint64_t enpassant_keys[64];
uint64_t castle_keys[16];
uint64_t side_key;

void init_random_hash_keys()
{
    // Init piece_keys.
    for (int piece = WP; piece <= BK; piece++)
    {
        if (piece == 7 || piece == 8)
        {
            for (int sq = SQ_A1; sq <= SQ_H8; sq++)
            {
                piece_keys[piece][sq] = 0;
            }
        }
        else
        {
            for (int sq = SQ_A1; sq <= SQ_H8; sq++)
            {
                piece_keys[piece][sq] = genrand_int64();
            }
        }
    }

    // Init enpassant_keys
    for (int sq = SQ_A1; sq <= SQ_H8; sq++)
    {
        enpassant_keys[sq] = genrand_int64();
    }

    // Init castle_keys
    for (int index = 0; index < 16; index++)
    {
        castle_keys[index] = genrand_int64();
    }

    // Init side_key
    side_key = genrand_int64();
}

uint64_t generate_hash_key_from_scratch(Position *pos)
{
    uint64_t final_hash_key = 0ULL;

    for (int sq = SQ_A1; sq <= SQ_H8; sq++)
    {
        int piece = pos->board[sq];
        final_hash_key ^= piece_keys[piece][sq];
    }

    // printf("pieces key %" PRIu64 "\n", final_hash_key);

    final_hash_key ^= castle_keys[pos->castling];

    int ep_square = PopLSB(pos->enpassantSquare);

    if (ep_square != 0)
    {
        final_hash_key ^= enpassant_keys[ep_square];
    }

    if (pos->sideToMove == COLOR_BLACK)
    {
        final_hash_key ^= side_key;
    }

    return final_hash_key;
}