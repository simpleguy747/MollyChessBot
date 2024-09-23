#include "mvvlva.h"
#include "position.h"
#include "movegen.h"
#include "pieces.h"

void calculate_mvv_lva(const Position *position, Move *move_param)
{
    int sq_from = SQ_FROM(move_param->move);
    int sq_to = SQ_TO(move_param->move);
    int attacker = position->board[sq_from];
    int victim = position->board[sq_to];
    int mvv = 6 * TYPE_OF_PIECE(victim);
    int lva = TYPE_OF_PIECE(attacker);
    int mvv_lva_score = 0;
    if (victim != EMPTY)
    {
        mvv_lva_score = mvv - lva;
    }
    else
    {
        mvv_lva_score = 0;
    }

    move_param->mvv_lva_value = mvv_lva_score;
}
