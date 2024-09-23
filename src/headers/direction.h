#ifndef DIRECTION_H /* Include guard */
#define DIRECTION_H

#include <stdint.h>

#define NORTH 8
#define SOUTH -NORTH
#define EAST 1
#define WEST -EAST
#define NORTH_WEST (NORTH + WEST)
#define NORTH_EAST (NORTH + EAST)
#define SOUTH_EAST (SOUTH + EAST)
#define SOUTH_WEST (SOUTH + WEST)

// #define SHIFT_UP(color,bitBoard)  ((bitBoard<<8)>>(16*color))

static inline uint64_t SHIFT_UP(int color, uint64_t bitBoard)
{
    return (bitBoard << 8) >> (16 * color);
}

#endif
