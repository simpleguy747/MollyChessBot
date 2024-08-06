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
#include "eval.h"
#include "mvvlva.h"

void sort_moves(const Position *position, MoveList *moveList)
{
    // Sort moves by MVV/LVA score
    for (int i = 0; i < moveList->count; i++)
    {
        for (int j = i + 1; j < moveList->count; j++)
        {
            if (moveList->moves[i].mvv_lva_value < moveList->moves[j].mvv_lva_value)
            {
                Move temp = moveList->moves[i];
                moveList->moves[i] = moveList->moves[j];
                moveList->moves[j] = temp;
            }
        }
    }
}

void generate_capture_moves(const int us, const Position *pos, MoveList *moveList, const uint64_t emptyBitboard, uint64_t enemyBitboard, int forwardDirection)
{
    generate_pawn_captures_and_promotions(us, pos, moveList, enemyBitboard, forwardDirection);
    generate_knight_moves(us, pos, moveList, enemyBitboard, MOVE_TYPE_KNIGHT);
    generate_king_non_castle_moves(us, pos, moveList, enemyBitboard, MOVE_TYPE_KING);
    generate_queen_moves(us, pos, moveList, enemyBitboard, ~emptyBitboard, MOVE_TYPE_QUEEN);
    generate_bishop_moves(us, pos, moveList, enemyBitboard, ~emptyBitboard, MOVE_TYPE_BISHOP);
    generate_rook_moves(us, pos, moveList, enemyBitboard, ~emptyBitboard, MOVE_TYPE_ROOK);
    sort_moves(pos, moveList);
}

void generate_non_captures(const int us, const Position *pos, MoveList *moveList, const uint64_t emptyBitboard, uint64_t enemyBitboard, int forwardDirection)
{
    generate_pawn_non_captures_and_promotions(us, pos, moveList, emptyBitboard, forwardDirection);
    generate_knight_moves(us, pos, moveList, emptyBitboard, MOVE_TYPE_KNIGHT);
    generate_king_non_castle_moves(us, pos, moveList, emptyBitboard, MOVE_TYPE_KING);
    generate_castling_moves(us, pos->castling, ~emptyBitboard, pos, moveList);
    generate_queen_moves(us, pos, moveList, emptyBitboard, ~emptyBitboard, MOVE_TYPE_QUEEN);
    generate_bishop_moves(us, pos, moveList, emptyBitboard, ~emptyBitboard, MOVE_TYPE_BISHOP);
    generate_rook_moves(us, pos, moveList, emptyBitboard, ~emptyBitboard, MOVE_TYPE_ROOK);
}

void generate_qsearch_moves(Position *pos, MoveList *moveList)
{
    moveList->count = 0;
    const int us = pos->sideToMove;
    const int forwardDirection = 8 - (16 * us);
    const uint64_t emptyBitboard = pos->type_of_pieces[EMPTY];
    const uint64_t enemyPiecesBitBoard = pos->occupancy_by_color[us ^ 1];
    // const uint64_t notOurPieces = ~pos->occupancy_by_color[us];
    // const uint64_t occupied = ~pos->type_of_pieces[EMPTY];

    generate_capture_moves(us, pos, moveList, emptyBitboard, enemyPiecesBitBoard, forwardDirection);
    // generate_non_captures(us, pos, moveList, emptyBitboard, enemyPiecesBitBoard, forwardDirection);
}

void generate_moves(Position *pos, MoveList *moveList)
{
    moveList->count = 0;
    const int us = pos->sideToMove;
    const int forwardDirection = 8 - (16 * us);
    const uint64_t emptyBitboard = pos->type_of_pieces[EMPTY];
    const uint64_t enemyPiecesBitBoard = pos->occupancy_by_color[us ^ 1];
    // const uint64_t notOurPieces = ~pos->occupancy_by_color[us];
    // const uint64_t occupied = ~pos->type_of_pieces[EMPTY];

    generate_capture_moves(us, pos, moveList, emptyBitboard, enemyPiecesBitBoard, forwardDirection);
    generate_non_captures(us, pos, moveList, emptyBitboard, enemyPiecesBitBoard, forwardDirection);

    // generate_pawn_moves(us, pos, moveList, emptyBitboard, enemyPiecesBitBoard, forwardDirection);
    // generate_knight_moves(us, pos, moveList, notOurPieces, MOVE_TYPE_KNIGHT);

    // generate_king_non_castle_moves(us, pos, moveList, notOurPieces, MOVE_TYPE_KING);
    // generate_castling_moves(us, pos->castling, occupied, pos, moveList);
    // generate_queen_moves(us, pos, moveList, notOurPieces, occupied, MOVE_TYPE_QUEEN);
    // generate_bishop_moves(us, pos, moveList, notOurPieces, occupied, MOVE_TYPE_BISHOP);
    // generate_rook_moves(us, pos, moveList, notOurPieces, occupied, MOVE_TYPE_ROOK);
}
