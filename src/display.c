#include <stdio.h>
#include "direction.h"
#include "display.h"
#include "pieces.h"
#include "position.h"
#include "squares.h"

// Display the board.
void DisplayBoard(Position *pos)
{
    for (int r = 7; r >= 0; r--)
    {
        for (int c = 0; c <= 7; c++)
        {
            int sq = 8 * r + c;
            uint64_t sq_bb = (1ULL << sq);
            for (int p = EMPTY; p <= BK; p++)
            {

                if ((sq_bb & pos->pieces[p]) != 0)
                {
                    printf(" %c ", PIECES_STR[p]);
                }
            }
        }
        printf("\n");
    }
}