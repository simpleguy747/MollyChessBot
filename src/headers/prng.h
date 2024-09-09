#ifndef PRNG_H /* Include guard */
#define PRNG_H

#include <stdint.h>

uint32_t genrand_int32(void);
uint64_t genrand_int64(void);
void init_mersenne(void);


#endif