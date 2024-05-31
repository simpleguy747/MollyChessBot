#include "direction.h"
#include "display.h"
#include "movegen.h"
#include "pieces.h"
#include "position.h"
#include "squares.h"
#include <stdio.h>

// Display the board.
void DisplayBoard(Position *pos)
{
    for (int r = 7; r >= 0; r--)
    {
        for (int c = 0; c <= 7; c++)
        {
            int sq = 8 * r + c;
            printf(" %c ", PIECES_STR[pos->board[sq]]);
        }
        printf("\n");
    }
}

void DisplayMove(int move)
{
    int toSq = SQ_TO(move);
    int fromSq = SQ_FROM(move);

    int toSq_rank = toSq >> 3;
    int toSq_file = toSq & 7;

    int fromSq_rank = fromSq >> 3;
    int fromSq_file = fromSq & 7;

    int typeOfMove = move >> 12;
    char promotionPiece = '\0';

    switch (typeOfMove)
    {
    case MOVE_TYPE_PROMOTION_KNIGHT:
        promotionPiece = 'n';
        break;
    case MOVE_TYPE_PROMOTION_BISHOP:
        promotionPiece = 'b';
        break;
    case MOVE_TYPE_PROMOTION_ROOK:
        promotionPiece = 'r';
        break;
    case MOVE_TYPE_PROMOTION_QUEEN:
        promotionPiece = 'q';
        break;
    }

    printf("%c%c%c%c%c\n", FILES_STR[fromSq_file], RANKS_STR[fromSq_rank], FILES_STR[toSq_file], RANKS_STR[toSq_rank], promotionPiece);
}


void DisplayMoveAndNodes(int move, uint64_t nodes)
{
    int toSq = SQ_TO(move);
    int fromSq = SQ_FROM(move);

    int toSq_rank = toSq >> 3;
    int toSq_file = toSq & 7;

    int fromSq_rank = fromSq >> 3;
    int fromSq_file = fromSq & 7;

    int typeOfMove = move >> 12;
    char promotionPiece = '\0';

    switch (typeOfMove)
    {
    case MOVE_TYPE_PROMOTION_KNIGHT:
        promotionPiece = 'n';
        break;
    case MOVE_TYPE_PROMOTION_BISHOP:
        promotionPiece = 'b';
        break;
    case MOVE_TYPE_PROMOTION_ROOK:
        promotionPiece = 'r';
        break;
    case MOVE_TYPE_PROMOTION_QUEEN:
        promotionPiece = 'q';
        break;
    }

    printf("%c%c%c%c%c% ld\n", FILES_STR[fromSq_file], RANKS_STR[fromSq_rank], FILES_STR[toSq_file], RANKS_STR[toSq_rank], promotionPiece,nodes);
}