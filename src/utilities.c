#include "string.h"
#include "utilities.h"
#include <stdint.h>
#include <sys/time.h>

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

long long GetCurrentTimeInMilliseconds()
{
  struct timeval currentTime;
  gettimeofday(&currentTime, NULL);
  return currentTime.tv_sec * 1000LL + currentTime.tv_usec / 1000LL;
}


