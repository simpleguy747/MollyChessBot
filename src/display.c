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
            int piece = EMPTY;
            for (int type_of_piece = EMPTY; type_of_piece <= KING; type_of_piece++)
            {

                for (int color_of_piece = COLOR_WHITE; color_of_piece <= COLOR_BLACK; color_of_piece++)
                {

                    if ((sq_bb & pos->type_of_pieces[type_of_piece] & pos->occupancy[color_of_piece]) != 0)
                    {
                        piece = MAKE_PIECE(type_of_piece, color_of_piece);
                    }
                }
            }
            printf(" %c ", PIECES_STR[piece]);
        }
        printf("\n");
    }
}