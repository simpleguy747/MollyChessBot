#ifndef ATTACK_MANAGER_H /* Include guard */
#define ATTACK_MANAGER_H

#include <stdint.h>
#include "position.h"

uint64_t is_square_attacked(int square, const Position *pos);
uint64_t is_check(const Position *pos);

#endif