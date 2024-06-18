#include "direction.h"
#include "display.h"
#include "movegen.h"
#include "pieces.h"
#include "position.h"
#include "squares.h"
#include <stdio.h>
#include "string.h"
#include "gen_moves_base.h"
// Display the board.
void DisplayBoard(Position *pos)
{
    for (char r = 7; r >= 0; r--)
    {
        for (char c = 0; c <= 7; c++)
        {
            int sq = 8 * r + c;
            printf(" %c ", PIECES_STR[(int)pos->board[sq]]);
        }
        printf("\n");
    }
}

void MoveStrFromInt(int move, char *s)
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

    s[0] = FILES_STR[fromSq_file];
    s[1] = RANKS_STR[fromSq_rank];
    s[2] = FILES_STR[toSq_file];
    s[3] = RANKS_STR[toSq_rank];
    s[4] = promotionPiece;
    s[5]='\0';
}

int MoveIntFromStr(char *s)
{
    int fromSq = (s[0] - 'a') + 8 * (s[1] - '1');
    int toSq = (s[2] - 'a') + 8 * (s[3] - '1');
    int move = ENCODE_MOVE(0, fromSq, toSq);
    return move;
}
void DisplayMove(int move)
{
    char s[6];
    MoveStrFromInt(move, s);
    printf("%s\n", s);
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

    printf("%c%c%c%c%c% ld\n", FILES_STR[fromSq_file], RANKS_STR[fromSq_rank], FILES_STR[toSq_file], RANKS_STR[toSq_rank], promotionPiece, nodes);
}