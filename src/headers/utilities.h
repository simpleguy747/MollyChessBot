#ifndef UTILITIES_H /* Include guard */
#define UTILITIES_H

#include <stdint.h>

int index_of(char *str, char c);
void find_next_space(char *fen, char **ptr);
long long get_current_time_in_milliseconds();

#define PopLSB(bb) ((bb) ? __builtin_ctzll(bb) : 0)
#define GetRankFromSquare(sq) (sq) >> 3
#define GetFileFromSquare(sq) (sq) & 7

#endif
