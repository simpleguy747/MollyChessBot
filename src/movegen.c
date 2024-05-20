#include "attacks.h"
#include "direction.h"
#include "gen_pawn_moves.h"
#include "gen_knight_moves.h"
#include "gen_king_moves.h"
#include "movegen.h"
#include "pieces.h"
#include "position.h"
#include "squares.h"
#include "utilities.h"


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