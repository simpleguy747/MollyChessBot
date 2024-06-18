
#include "eval.h"
#include "pieces.h"
#include "position.h"
#include "color.h"

const int MaterialValue[] = {0, 100, 300, 315, 500, 900};

int Evaluate(Position *pos)
{
    int eval_by_color[2] = {0, 0};
    for (int color = COLOR_WHITE; color <= COLOR_BLACK; color++)
    {
        for (int pt = PAWN; pt < KING; pt++)
        {
            uint64_t piece_of_color = pos->occupancy_by_color[color] & pos->type_of_pieces[pt];
            int count_pieces = __builtin_popcountll(piece_of_color);
            eval_by_color[color] += count_pieces * MaterialValue[pt];
        }
    }

    return (eval_by_color[COLOR_WHITE] - eval_by_color[COLOR_BLACK]) * (1 - (2 * pos->sideToMove));
}