#include "squares.h"
#include <stdint.h>

const uint64_t ColorWiseRanks[2][8] = {
    {RANK_1_BB, RANK_2_BB, RANK_3_BB, RANK_4_BB, RANK_5_BB, RANK_6_BB, RANK_7_BB, RANK_8_BB},
    {RANK_8_BB, RANK_7_BB, RANK_6_BB, RANK_5_BB, RANK_4_BB, RANK_3_BB, RANK_2_BB, RANK_1_BB}};

const uint64_t ColorWiseEnpassantRanks[2][2] = {{0x000000FE00000000ULL, 0x000007F00000000ULL}, {0x00000000FE000000UL, 0x000000007F000000ULL}};