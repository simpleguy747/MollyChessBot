#include "tuner.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "position.h"
#include "fen_manager.h"
#include "display.h"
#include "eval.h"
#include "math.h"
// pieces
#define MAX_LINE_LENGTH 1024
FenWithResult parse_fen(const char *fen_string)
{
    FenWithResult fenWithResult={0};
    char *fen = strdup(fen_string);
    char *space_ptr = strrchr(fen, ' '); // Find last space
    if (space_ptr != NULL)
    {
        *space_ptr = '\0'; // Split at last space
        char *result = space_ptr + 1;
        result[strcspn(result, ";")] = 0; // Remove semicolon

        // Remove "c9"
        char *c9_ptr = strstr(fen, "c9");
        if (c9_ptr != NULL)
        {
            *c9_ptr = ' ';
        }

        // Remove trailing spaces
        while (fen[strlen(fen) - 1] == ' ')
        {
            fen[strlen(fen) - 1] = '\0';
        }

        strcpy(fenWithResult.str_fen, fen);
        strcpy(fenWithResult.str_result, result);

        if (strcmp(result, "\"0-1\"") == 0)
        {
            fenWithResult.float_result = -1;
        }
        else if (strcmp(result, "\"1-0\"") == 0)
        {
            fenWithResult.float_result = 1;
        }
        else
        {
            fenWithResult.float_result = 0.5;
        }
    }
    return fenWithResult;
}

float compute_sigmoid(float K, int score)
{
    float sigmoid = 0;//1 / (1 + pow(10, -K * score / 400));
    return sigmoid;
}

void print_game(const FenWithResult *game)
{
    printf("FEN: %s\n", game->str_fen);
    printf("Result: %s\n", game->str_result);
    printf("Result: %lf\n\n", game->float_result);
}
int read_from_file()
{
    const char *filename = "engine-test/fen-files/quiet-labeled.v7.sample.epd";
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        perror(filename);
        return 1;
    }

    FenWithResult *games = NULL;
    int numGames = 0;
    // int bufferSize = 100; // Initial buffer size

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, fp))
    {
        // Remove newline character
        line[strcspn(line, "\n")] = 0;
        printf("%s\n", line);
        // Reallocate memory if needed

        games = realloc(games, (numGames + 1) * sizeof(FenWithResult));
        if (!games)
        {
            perror("realloc");
            return 1;
        }

        // Parse line
        FenWithResult game = parse_fen(line);
        games[numGames] = game;

        numGames++;
    }

    fclose(fp);

    free(games);
    return 0;
}
void tune()
{
    Position pos;
    FenWithResult fenWithResult = parse_fen("r2qkr2/p1pp1ppp/1pn1pn2/2P5/3Pb3/2N1P3/PP3PPP/R1B1KB1R b KQq - 0 1 c9 0-1");
    set_board_from_fen(fenWithResult.str_fen, &pos);
    display_board(&pos);
    int eval = evaluate(&pos);
    float sigmoid = compute_sigmoid(0.2, eval);
    printf("%lf\n", sigmoid);
    read_from_file();
}
