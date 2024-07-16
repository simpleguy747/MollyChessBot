#include "attacks.h"
#include "direction.h"
#include "gen_bishop_moves.h"
#include "gen_king_moves.h"
#include "gen_knight_moves.h"
#include "gen_pawn_moves.h"
#include "gen_rook_moves.h"
#include "gen_queen_moves.h"
#include "movegen.h"
#include "pieces.h"
#include "position.h"
#include "squares.h"
#include "utilities.h"


void generate_moves(Position *pos, MoveList *moveList)
{
    moveList->count = 0;
    const int us = pos->sideToMove;
    const int forwardDirection = 8 - (16 * us);
    const uint64_t emptyBitboard = pos->type_of_pieces[EMPTY];
    const uint64_t enemyPiecesBitBoard = pos->occupancy_by_color[us ^ 1];
    const uint64_t notOurPieces = ~pos->occupancy_by_color[us];
    const uint64_t occupied = ~pos->type_of_pieces[EMPTY];
    generate_pawn_moves(us, pos, moveList, emptyBitboard, enemyPiecesBitBoard, forwardDirection);
    generate_knight_moves(us, pos, moveList, notOurPieces, MOVE_TYPE_KNIGHT);
    generate_king_non_castle_moves(us, pos, moveList, notOurPieces, MOVE_TYPE_KING);
    generate_castling_moves(us,pos->castling,occupied,pos,moveList);
    generate_queen_moves(us, pos, moveList, notOurPieces,occupied, MOVE_TYPE_QUEEN);
    generate_bishop_moves(us, pos, moveList, notOurPieces,occupied, MOVE_TYPE_BISHOP);
    generate_rook_moves(us, pos, moveList, notOurPieces,occupied, MOVE_TYPE_ROOK);
}