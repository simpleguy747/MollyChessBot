#ifndef UTILITIES_H /* Include guard */
#define UTILITIES_H
#include <stdint.h>
int indexOf(char *str, char c);
void FindNextSpace(char *fen, char **ptr);
int PopLSB(uint64_t bb);
#endif