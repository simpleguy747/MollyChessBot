#include "direction.h"
#include "gen_pawn_moves.h"
#include "gen_moves_base.h"
#include "pieces.h"
#include "position.h"
#include "squares.h"
#include "utilities.h"
#include <stdint.h>

void CreatePawnMoves(int typeOfMove, int offset, uint64_t movesBitBoard, MoveList *moveList)
{
    for (; movesBitBoard > 0; movesBitBoard &= movesBitBoard - 1)
    {
        int sqTo = PopLSB(movesBitBoard);
        int sqFrom = sqTo + offset;
        moveList->moves[moveList->count].move = ENCODE_MOVE(typeOfMove, sqFrom, sqTo);
        moveList->count++;
    }
}

void CreatePromotionMoves(int offset, uint64_t movesBitBoard, MoveList *moveList)
{
    for (; movesBitBoard > 0; movesBitBoard &= movesBitBoard - 1)
    {
        int sqTo = PopLSB(movesBitBoard);
        int sqFrom = sqTo + offset;
        moveList->moves[moveList->count++].move = ENCODE_MOVE(PROMOTION_QUEEN, sqFrom, sqTo);
        moveList->moves[moveList->count++].move = ENCODE_MOVE(PROMOTION_ROOK, sqFrom, sqTo);
        moveList->moves[moveList->count++].move = ENCODE_MOVE(PROMOTION_BISHOP, sqFrom, sqTo);
        moveList->moves[moveList->count++].move = ENCODE_MOVE(PROMOTION_KNIGHT, sqFrom, sqTo);
    }
}

void GeneratePawnNonCapturePromoMoves(const int us, const Position *pos, MoveList *moveList, const uint64_t targetBitboard, int forwardDirection)
{
    uint64_t ourPawns = pos->type_of_pieces[PAWN] & pos->occupancy_by_color[us];
    // Single push for pawns not on 7th-rank.
    uint64_t ourPawnsNonPromoting = SHIFT_UP(us, (ourPawns & ~ColorWiseRanks[us][RANK_7]));
    // Double push the pawns from starting rank.
    uint64_t ourPawnsDoublePush = SHIFT_UP(us, (ourPawnsNonPromoting & ColorWiseRanks[us][RANK_3]));
    // Single push to promotion
    uint64_t ourPawnsPromoting = SHIFT_UP(us, (ourPawns & ColorWiseRanks[us][RANK_7]));
    CreatePawnMoves(NO_CAP, -forwardDirection, ourPawnsNonPromoting, moveList);
    CreatePawnMoves(NO_CAP, -2 * forwardDirection, ourPawnsDoublePush, moveList);
    CreatePromotionMoves(-forwardDirection, ourPawnsPromoting, moveList);
}

void GeneratePawnCapturesAndPromotions(const int us, const Position *pos, MoveList *moveList, const uint64_t targetBitboard, int forwardDirection)
{
    uint64_t ourPawns = pos->type_of_pieces[PAWN] & pos->occupancy_by_color[us];
    uint64_t pawnCaptures = (((ourPawns & NOT_FILE_A_BB) << 7) >> (16 * us)) & targetBitboard;
    uint64_t pawnCapturesPromoting = pawnCaptures & ColorWiseRanks[us][RANK_8];
    uint64_t pawnCapturesNonPromoting = pawnCaptures & ~pawnCapturesPromoting;
    uint64_t enpassantSquareBB = pos->enpassantSquare;
    uint64_t epCapture = (((ourPawns & ColorWiseEnpassantRanks[us][0]) << 7) >> (16 * us)) & enpassantSquareBB;

    CreatePawnMoves(CAP, (-forwardDirection + 1), pawnCapturesNonPromoting, moveList);
    CreatePawnMoves(ENPASSANT, (-forwardDirection + 1), epCapture, moveList);
    CreatePromotionMoves((-forwardDirection + 1), pawnCapturesPromoting, moveList);

    pawnCaptures = (((ourPawns & NOT_FILE_H_BB) << 9) >> (16 * us)) & targetBitboard;
    pawnCapturesPromoting = pawnCaptures & ColorWiseRanks[us][RANK_8];
    pawnCapturesNonPromoting = pawnCaptures & ~pawnCapturesPromoting;
    epCapture = (((ourPawns & ColorWiseEnpassantRanks[us][1]) << 9) >> (16 * us)) & enpassantSquareBB;

    CreatePawnMoves(CAP, (-forwardDirection - 1), pawnCapturesNonPromoting, moveList);
    CreatePawnMoves(ENPASSANT, (-forwardDirection - 1), epCapture, moveList);
    CreatePromotionMoves((-forwardDirection - 1), pawnCapturesPromoting, moveList);
}

void GeneratePawnMoves(const int us, const Position *pos, MoveList *moveList, const uint64_t emptyBitboard, uint64_t enemyBitboard, int forwardDirection)
{
    GeneratePawnNonCapturePromoMoves(us, pos, moveList, emptyBitboard, forwardDirection);
    GeneratePawnCapturesAndPromotions(us, pos, moveList, enemyBitboard, forwardDirection);
}