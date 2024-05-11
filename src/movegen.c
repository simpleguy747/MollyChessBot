#include "attacks.h"
#include "direction.h"
#include "gen_pawn_moves.h"
#include "movegen.h"
#include "pieces.h"
#include "position.h"
#include "squares.h"
#include "utilities.h"

void CreateMoves(const int typeOfMove, const int sqFrom, uint64_t movesBitBoard, MoveList *moveList)
{
    for (; movesBitBoard > 0; movesBitBoard &= movesBitBoard - 1)
    {
        int sqTo = PopLSB(movesBitBoard);
        moveList->moves[moveList->count].move = ENCODE_MOVE(typeOfMove, sqFrom, sqTo);
        moveList->count++;
    }
}

void GenerateKnightMoves(const int us, const Position *pos, MoveList *moveList, const uint64_t targetBitboard, int typeOfMove)
{
    uint64_t ourKnights = pos->type_of_pieces[KNIGHT] & pos->occupancy_by_color[us];
    for (; ourKnights > 0; ourKnights &= ourKnights - 1)
    {
        int sqFrom = PopLSB(ourKnights);
        uint64_t knightAttacksFromSquare = KNIGHT_ATTACKS[sqFrom] & targetBitboard;
        CreateMoves(typeOfMove, sqFrom, knightAttacksFromSquare, moveList);
    }
}

void GenerateKingNonCastleMoves(const int us, const Position *pos, MoveList *moveList, const uint64_t targetBitboard, int typeOfMove)
{
    uint64_t ourKing = pos->type_of_pieces[KING] & pos->occupancy_by_color[us];
    for (; ourKing > 0; ourKing &= ourKing - 1)
    {
        int sqFrom = PopLSB(ourKing);
        uint64_t kingAttacksFromSquare = KING_ATTACKS[sqFrom] & targetBitboard;
        CreateMoves(typeOfMove, sqFrom, kingAttacksFromSquare, moveList);
    }
}

void GenerateMoves(Position *pos, MoveList *moveList)
{
    const int us = pos->sideToMove;

    const int forwardDirection = 8 - (16 * us);
    const uint64_t emptyBitboard = pos->type_of_pieces[EMPTY];
    const uint64_t enemyPiecesBitBoard = pos->occupancy_by_color[us ^ 1];
    GeneratePawnMoves(us, pos, moveList, emptyBitboard, enemyPiecesBitBoard, forwardDirection);
    GenerateKnightMoves(us, pos, moveList, emptyBitboard, NO_CAP);
    GenerateKingNonCastleMoves(us, pos, moveList, emptyBitboard, NO_CAP);
}