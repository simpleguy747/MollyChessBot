#ifndef MAGIC_BITBOARDS_H_INCLUDED
#define MAGIC_BITBOARDS_H_INCLUDED

#include <stdint.h>
 
typedef struct Magic
{
    uint64_t mask;
    uint64_t magic;
    uint64_t *attacks;
    int shift;

} Magic;

extern Magic RookMagics[64];
extern Magic BishopMagics[64];

extern uint64_t RookTable[0x19000];  // To store rook attacks
extern uint64_t BishopTable[0x1480]; // To store bishop attacks

void InitMagicsAll();

#endif