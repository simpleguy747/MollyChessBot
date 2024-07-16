#include "init.h"
#include "position.h"
#include "stdint.h"
#include "string.h"

void init_all(Position *position)
{
    memset(position->board, 0, 64 * sizeof(char));
    memset(position->type_of_pieces, 0, 7 * sizeof(uint64_t));
    memset(position->occupancy_by_color, 0, 2 * sizeof(uint64_t));
    position->castling = 0;
    position->enpassantSquare = 0;
}
