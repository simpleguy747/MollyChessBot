#include "direction.h"
#include "gen_moves_base.h"
#include "gen_pawn_moves.h"
#include "pieces.h"
#include "position.h"
#include "squares.h"
#include "utilities.h"
#include "mvvlva.h"
#include <stdint.h>

void CreatePawnMoves(const Position*pos,int typeOfMove, int offset, uint64_t movesBitBoard, MoveList *moveList)
{
    for (; movesBitBoard > 0; movesBitBoard &= movesBitBoard - 1)
    {
        int sqTo = PopLSB(movesBitBoard);
        int sqFrom = sqTo + offset;
        moveList->moves[moveList->count].move = ENCODE_MOVE(typeOfMove, sqFrom, sqTo);
        calculate_mvv_lva(pos,&moveList->moves[moveList->count]);
        moveList->count++;
    }
}

void CreatePromotionMoves(const Position*pos,int offset, uint64_t movesBitBoard, MoveList *moveList)
{
    for (; movesBitBoard > 0; movesBitBoard &= movesBitBoard - 1)
    {
        int sqTo = PopLSB(movesBitBoard);
        int sqFrom = sqTo + offset;
        moveList->moves[moveList->count++].move = ENCODE_MOVE(MOVE_TYPE_PROMOTION_QUEEN, sqFrom, sqTo);
        calculate_mvv_lva(pos,&moveList->moves[moveList->count]);
        moveList->moves[moveList->count++].move = ENCODE_MOVE(MOVE_TYPE_PROMOTION_ROOK, sqFrom, sqTo);
        calculate_mvv_lva(pos,&moveList->moves[moveList->count]);
        moveList->moves[moveList->count++].move = ENCODE_MOVE(MOVE_TYPE_PROMOTION_BISHOP, sqFrom, sqTo);
        calculate_mvv_lva(pos,&moveList->moves[moveList->count]);
        moveList->moves[moveList->count++].move = ENCODE_MOVE(MOVE_TYPE_PROMOTION_KNIGHT, sqFrom, sqTo);
        calculate_mvv_lva(pos,&moveList->moves[moveList->count]);
    }
}

void generate_pawn_non_captures_and_promotions(const int us, const Position *pos, MoveList *moveList, const uint64_t targetBitboard, int forwardDirection)
{
    uint64_t ourPawns = pos->type_of_pieces[PAWN] & pos->occupancy_by_color[us];
    // Single push for pawns not on 7th-rank.
    uint64_t ourPawnsNonPromoting = SHIFT_UP(us, (ourPawns & ~Color_Wise_Ranks[us][RANK_7])) & targetBitboard;
    // Double push the pawns from starting rank.
    uint64_t ourPawnsDoublePush = SHIFT_UP(us, (ourPawnsNonPromoting & Color_Wise_Ranks[us][RANK_3])) & targetBitboard;
    // Single push to promotion
    uint64_t ourPawnsPromoting = SHIFT_UP(us, (ourPawns & Color_Wise_Ranks[us][RANK_7]))& targetBitboard;
    CreatePawnMoves(pos,MOVE_TYPE_PAWN, -forwardDirection, ourPawnsNonPromoting, moveList);
    CreatePawnMoves(pos,MOVE_TYPE_PAWN, -2 * forwardDirection, ourPawnsDoublePush, moveList);
    CreatePromotionMoves(pos,-forwardDirection, ourPawnsPromoting, moveList);
}

void generate_pawn_captures_and_promotions(const int us, const Position *pos, MoveList *moveList, const uint64_t targetBitboard, int forwardDirection)
{
    uint64_t ourPawns = pos->type_of_pieces[PAWN] & pos->occupancy_by_color[us];
    uint64_t pawnCaptures = (((ourPawns & NOT_FILE_A_BB) << 7) >> (16 * us)) & targetBitboard;
    uint64_t pawnCapturesPromoting = pawnCaptures & Color_Wise_Ranks[us][RANK_8];
    uint64_t pawnCapturesNonPromoting = pawnCaptures & ~pawnCapturesPromoting;
    uint64_t enpassantSquareBB = pos->enpassantSquare;
    uint64_t epCapture = (((ourPawns & Color_Wise_Enpassant_Ranks[us][0]) << 7) >> (16 * us)) & enpassantSquareBB;

    CreatePawnMoves(pos,MOVE_TYPE_PAWN, (-forwardDirection + 1), pawnCapturesNonPromoting, moveList);
    CreatePawnMoves(pos,MOVE_TYPE_ENPASSANT, (-forwardDirection + 1), epCapture, moveList);
    CreatePromotionMoves(pos,(-forwardDirection + 1), pawnCapturesPromoting, moveList);

    pawnCaptures = (((ourPawns & NOT_FILE_H_BB) << 9) >> (16 * us)) & targetBitboard;
    pawnCapturesPromoting = pawnCaptures & Color_Wise_Ranks[us][RANK_8];
    pawnCapturesNonPromoting = pawnCaptures & ~pawnCapturesPromoting;
    epCapture = (((ourPawns & Color_Wise_Enpassant_Ranks[us][1]) << 9) >> (16 * us)) & enpassantSquareBB;

    CreatePawnMoves(pos,MOVE_TYPE_PAWN, (-forwardDirection - 1), pawnCapturesNonPromoting, moveList);
    CreatePawnMoves(pos,MOVE_TYPE_ENPASSANT, (-forwardDirection - 1), epCapture, moveList);
    CreatePromotionMoves(pos,(-forwardDirection - 1), pawnCapturesPromoting, moveList);
}

void generate_pawn_moves(const int us, const Position *pos, MoveList *moveList, const uint64_t emptyBitboard, int forwardDirection)
{
    generate_pawn_non_captures_and_promotions(us, pos, moveList, emptyBitboard, forwardDirection);
}