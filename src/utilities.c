#include "string.h"
#include "utilities.h"
#include <stdint.h>

int indexOf(char *str, char c)
{
    int string_length = strlen(str);
    for (int index = 0; index < string_length; index++)
    {
        if (str[index] == c)
        {
            return index;
        }
    }
    return -1;
}

void FindNextSpace(char *fen, char **ptr)
{
    while (*fen && *fen != ' ')
    {
        ++fen;
    }
    *ptr = (*fen == ' ') ? fen + 1 : NULL;
}

// inline int PopLSB(uint64_t bb)
// {
//     return __builtin_ctzll(bb);
// }

