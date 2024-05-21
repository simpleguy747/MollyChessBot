
#ifndef ATTACKS_H /* Include guard */
#define ATTACKS_H

#include<stdint.h>

extern const uint64_t KNIGHT_ATTACKS[64];
extern const uint64_t KING_ATTACKS[64];

uint64_t GenerateRookAttacks(int sqFrom, uint64_t occupied);
uint64_t GenerateBishopAttacks(int sqFrom, uint64_t occupied);
#endif