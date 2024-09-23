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

extern Magic Rook_Magics[64];
extern Magic Bishop_Magics[64];

extern uint64_t Rook_Table[0x19000];  // To store rook attacks
extern uint64_t Bishop_Table[0x1480]; // To store bishop attacks

void init_magics_all();

#endif
