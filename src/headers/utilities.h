#ifndef UTILITIES   /* Include guard */
#define UTILITIES

#include "string.h"

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

#endif