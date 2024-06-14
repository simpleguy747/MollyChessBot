#ifndef UTILITIES_H /* Include guard */
#define UTILITIES_H

#include <stdint.h>

int indexOf(char *str, char c);
void FindNextSpace(char *fen, char **ptr);
long long GetCurrentTimeInMilliseconds();

#define PopLSB(bb) __builtin_ctzll(bb)
#define GetRankFromSquare(sq) (sq) >> 3
#define GetFileFromSquare(sq) (sq) & 7

#endif