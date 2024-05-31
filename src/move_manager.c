#include "position.h"
#include <stdint.h>
#include "movegen.h"
#include "pieces.h"
#include "castling_permissions.h"

void MakeMove(Position *pos, int move)
{
    const int sq_from = (SQ_FROM(move));
    const int sq_to = (SQ_TO(move));
    const int type_of_move = (TYPE_OF_MOVE(move));
    const uint64_t sq_from_bb = 1ULL << sq_from;
    const uint64_t sq_to_bb = 1ULL << sq_to;

    const int us = pos->sideToMove;
    const int enemy = us ^ 1;

    pos->occupancy_by_color[enemy] &= ~sq_to_bb;
    pos->occupancy_by_color[us] ^= (sq_from_bb | sq_to_bb);

    pos->enpassantSquare = EMPTY;
    pos->type_of_pieces[TYPE_OF_PIECE(pos->board[sq_to])] &= ~sq_to_bb;
    pos->castling &= ~CastleRightsConsts[sq_to];
    
    switch (type_of_move)
    {
    case MOVE_TYPE_PAWN:
        pos->type_of_pieces[PAWN] ^= (sq_from_bb | sq_to_bb);
        pos->enpassantSquare = (((sq_from_bb << 8) >> (16 * us)) & ((sq_to_bb >> 8) << (16 * us)));
        pos->board[sq_to] = MAKE_PIECE(PAWN, us);
        pos->board[sq_from] = EMPTY;
        break;

    case MOVE_TYPE_KNIGHT:
        pos->type_of_pieces[KNIGHT] ^= (sq_from_bb | sq_to_bb);
        pos->board[sq_to] = MAKE_PIECE(KNIGHT, us);
        pos->board[sq_from] = EMPTY;
        break;

    case MOVE_TYPE_BISHOP:
        pos->type_of_pieces[BISHOP] ^= (sq_from_bb | sq_to_bb);
        pos->board[sq_to] = MAKE_PIECE(BISHOP, us);
        pos->board[sq_from] = EMPTY;
        break;

    case MOVE_TYPE_ROOK:
        pos->type_of_pieces[ROOK] ^= (sq_from_bb | sq_to_bb);
        pos->castling &= ~CastleRightsConsts[sq_from];
        pos->board[sq_to] = MAKE_PIECE(ROOK, us);
        pos->board[sq_from] = EMPTY;
        break;

    case MOVE_TYPE_QUEEN:
        pos->type_of_pieces[QUEEN] ^= (sq_from_bb | sq_to_bb);
        pos->board[sq_to] = MAKE_PIECE(QUEEN, us);
        pos->board[sq_from] = EMPTY;
        break;

    case MOVE_TYPE_KING:
        pos->type_of_pieces[KING] ^= (sq_from_bb | sq_to_bb);
        pos->castling &= ~CastleRightsConsts[sq_from];
        pos->board[sq_to] = MAKE_PIECE(KING, us);
        pos->board[sq_from] = EMPTY;
        break;

    case MOVE_TYPE_PROMOTION_KNIGHT:
        pos->type_of_pieces[PAWN] ^= (sq_from_bb);
        pos->type_of_pieces[KNIGHT] ^= (sq_to_bb);
        pos->board[sq_to] = MAKE_PIECE(KNIGHT, us);
        pos->board[sq_from] = EMPTY;
        break;

    case MOVE_TYPE_PROMOTION_BISHOP:
        pos->type_of_pieces[PAWN] ^= (sq_from_bb);
        pos->type_of_pieces[BISHOP] ^= (sq_to_bb);
        pos->board[sq_to] = MAKE_PIECE(BISHOP, us);
        pos->board[sq_from] = EMPTY;
        break;

    case MOVE_TYPE_PROMOTION_ROOK:
        pos->type_of_pieces[PAWN] ^= (sq_from_bb);
        pos->type_of_pieces[ROOK] ^= (sq_to_bb);
        pos->board[sq_to] = MAKE_PIECE(ROOK, us);
        pos->board[sq_from] = EMPTY;
        break;

    case MOVE_TYPE_PROMOTION_QUEEN:
        pos->type_of_pieces[PAWN] ^= (sq_from_bb);
        pos->type_of_pieces[QUEEN] ^= (sq_to_bb);
        pos->board[sq_to] = MAKE_PIECE(QUEEN, us);
        pos->board[sq_from] = EMPTY;
        break;

    case MOVE_TYPE_ENPASSANT:
        pos->type_of_pieces[PAWN] ^= sq_from_bb | sq_to_bb | ((sq_to_bb >> 8) << (16 * us));
        pos->occupancy_by_color[enemy] &= ~((sq_to_bb >> 8) << (16 * us));
        pos->board[sq_to] = MAKE_PIECE(PAWN, us);
        int ep_pawn_sq = (sq_to - 8) + (16 * us);
        pos->board[ep_pawn_sq] = EMPTY;
        break;

    case MOVE_TYPE_CASTLE_KING_SIDE:
        pos->type_of_pieces[KING] ^= sq_from_bb | sq_to_bb;
        pos->castling &= ~CastleRightsConsts[sq_from];
        pos->type_of_pieces[ROOK] ^= Castled_Rook_Files[us][0];
        pos->occupancy_by_color[us] ^= Castled_Rook_Files[us][0];
        pos->board[sq_from] = EMPTY;
        pos->board[sq_to] = MAKE_PIECE(KING, us);
        pos->board[Castled_Rook_Squares[us][2]] = EMPTY;
        pos->board[Castled_Rook_Squares[us][3]] = MAKE_PIECE(ROOK, us);
        break;

    case MOVE_TYPE_CASTLE_QUEEN_SIDE:
        pos->type_of_pieces[KING] ^= sq_from_bb | sq_to_bb;
        pos->castling &= ~CastleRightsConsts[sq_from];
        pos->type_of_pieces[ROOK] ^= Castled_Rook_Files[us][1];
        pos->occupancy_by_color[us] ^= Castled_Rook_Files[us][1];
        pos->board[Castled_Rook_Squares[us][0]] = EMPTY;
        pos->board[Castled_Rook_Squares[us][1]] = MAKE_PIECE(ROOK, us);
        break;

    default:
        break;
    }

    pos->type_of_pieces[EMPTY] = ~(pos->occupancy_by_color[COLOR_WHITE] | pos->occupancy_by_color[COLOR_BLACK]);
}