#ifndef TUNER_H /* Include guard */
#define TUNER_H

#define MAX_FEN_LENGTH 150
typedef struct FenWithResult
{
    char str_fen[MAX_FEN_LENGTH];
    char str_result[4];
    float float_result;
} FenWithResult;
void tune();

#endif
