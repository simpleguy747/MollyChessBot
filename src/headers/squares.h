#ifndef SQUARES_H   /* Include guard */
#define SQUARES_H

#include<stdint.h>

#define SQ_A1 0
#define SQ_B1 1
#define SQ_C1 2
#define SQ_D1 3
#define SQ_E1 4
#define SQ_F1 5
#define SQ_G1 6
#define SQ_H1 7
#define SQ_A2 8
#define SQ_B2 9
#define SQ_C2 10
#define SQ_D2 11
#define SQ_E2 12
#define SQ_F2 13
#define SQ_G2 14
#define SQ_H2 15
#define SQ_A3 16
#define SQ_B3 17
#define SQ_C3 18
#define SQ_D3 19
#define SQ_E3 20
#define SQ_F3 21
#define SQ_G3 22
#define SQ_H3 23
#define SQ_A4 24
#define SQ_B4 25
#define SQ_C4 26
#define SQ_D4 27
#define SQ_E4 28
#define SQ_F4 29
#define SQ_G4 30
#define SQ_H4 31
#define SQ_A5 32
#define SQ_B5 33
#define SQ_C5 34
#define SQ_D5 35
#define SQ_E5 36
#define SQ_F5 37
#define SQ_G5 38
#define SQ_H5 39
#define SQ_A6 40
#define SQ_B6 41
#define SQ_C6 42
#define SQ_D6 43
#define SQ_E6 44
#define SQ_F6 45
#define SQ_G6 46
#define SQ_H6 47
#define SQ_A7 48
#define SQ_B7 49
#define SQ_C7 50
#define SQ_D7 51
#define SQ_E7 52
#define SQ_F7 53
#define SQ_G7 54
#define SQ_H7 55
#define SQ_A8 56
#define SQ_B8 57
#define SQ_C8 58
#define SQ_D8 59
#define SQ_E8 60
#define SQ_F8 61
#define SQ_G8 62
#define SQ_H8 63

#define SQ_NONE_BB 0

// FILES
#define FILE_A 0
#define FILE_B 1
#define FILE_C 2
#define FILE_D 3
#define FILE_E 4
#define FILE_F 5
#define FILE_G 6
#define FILE_H 7

// RANKS
#define RANK_1 0
#define RANK_2 1
#define RANK_3 2
#define RANK_4 3
#define RANK_5 4
#define RANK_6 5
#define RANK_7 6
#define RANK_8 7

// Bitboards for FILE
#define FILE_A_BB 0x0101010101010101ULL
#define FILE_B_BB 0x0202020202020202ULL
#define FILE_C_BB 0x0404040404040404ULL
#define FILE_D_BB 0x0808080808080808ULL
#define FILE_E_BB 0x1010101010101010ULL
#define FILE_F_BB 0x2020202020202020ULL
#define FILE_G_BB 0x4040404040404040ULL
#define FILE_H_BB 0x8080808080808080ULL

#define NOT_FILE_A_BB 0xfefefefefefefefeULL
#define NOT_FILE_H_BB 0x7f7f7f7f7f7f7f7fULL

// Bitboards for Ranks
#define RANK_1_BB 0x00000000000000ffULL
#define RANK_2_BB 0x000000000000ff00ULL
#define RANK_3_BB 0x0000000000ff0000ULL
#define RANK_4_BB 0x00000000ff000000ULL
#define RANK_5_BB 0x000000ff00000000ULL
#define RANK_6_BB 0x0000ff0000000000ULL
#define RANK_7_BB 0x00ff000000000000ULL
#define RANK_8_BB 0xff00000000000000ULL

// Files and ranks in string.
#define RANKS_STR "12345678"
#define FILES_STR "abcdefgh"
// Colorwise ranks.
extern const uint64_t ColorWiseRanks[2][8];
extern const uint64_t ColorWiseEnpassantRanks[2][2];


#endif