#include "position.h"
#include <stdint.h>
#include "movegen.h"
#include "pieces.h"
#include "castling_permissions.h"
#include "zobrist.h"
#include "utilities.h"
#include <inttypes.h>
void make_move(Position *pos, int move)
{
    const int sq_from = (SQ_FROM(move));
    const int sq_to = (SQ_TO(move));
    const int type_of_move = (TYPE_OF_MOVE(move));
    const uint64_t sq_from_bb = 1ULL << sq_from;
    const uint64_t sq_to_bb = 1ULL << sq_to;

    const int us = pos->sideToMove;
    const int enemy = us ^ 1;

    const int old_ep_square = PopLSB(pos->enpassantSquare);
    const int old_castle_rights = pos->castling;
    const int piece_moving = pos->board[sq_from];
    const int piece_captured = pos->board[sq_to];

    pos->occupancy_by_color[enemy] &= ~sq_to_bb;
    pos->occupancy_by_color[us] ^= (sq_from_bb | sq_to_bb);

    pos->enpassantSquare = EMPTY;
    pos->type_of_pieces[TYPE_OF_PIECE(pos->board[sq_to])] &= ~sq_to_bb;
    pos->castling &= ~Castle_Rights_Consts[sq_to];

    switch (type_of_move)
    {
    case MOVE_TYPE_PAWN:
        pos->type_of_pieces[PAWN] ^= (sq_from_bb | sq_to_bb);
        pos->enpassantSquare = (((sq_from_bb << 8) >> (16 * us)) & ((sq_to_bb >> 8) << (16 * us)));
        int piece = MAKE_PIECE(PAWN, us);
        pos->board[sq_to] = piece;
        pos->board[sq_from] = EMPTY;

        // Update hash keys
        pos->hash_key ^= piece_keys[piece_moving][sq_from] ^
                         piece_keys[piece_moving][sq_to] ^
                         piece_keys[piece_captured][sq_to];

        break;

    case MOVE_TYPE_KNIGHT:
        pos->type_of_pieces[KNIGHT] ^= (sq_from_bb | sq_to_bb);
        pos->board[sq_to] = MAKE_PIECE(KNIGHT, us);
        pos->board[sq_from] = EMPTY;

        // Update hash keys
        pos->hash_key ^= piece_keys[piece_moving][sq_from] ^
                         piece_keys[piece_moving][sq_to] ^
                         piece_keys[piece_captured][sq_to];
        break;

    case MOVE_TYPE_BISHOP:
        pos->type_of_pieces[BISHOP] ^= (sq_from_bb | sq_to_bb);
        pos->board[sq_to] = MAKE_PIECE(BISHOP, us);
        pos->board[sq_from] = EMPTY;

        // Update hash keys
        pos->hash_key ^= piece_keys[piece_moving][sq_from] ^
                         piece_keys[piece_moving][sq_to] ^
                         piece_keys[piece_captured][sq_to];
        break;

    case MOVE_TYPE_ROOK:
        pos->type_of_pieces[ROOK] ^= (sq_from_bb | sq_to_bb);
        pos->castling &= ~Castle_Rights_Consts[sq_from];
        pos->board[sq_to] = MAKE_PIECE(ROOK, us);
        pos->board[sq_from] = EMPTY;

        // Update hash keys
        pos->hash_key ^= piece_keys[piece_moving][sq_from] ^
                         piece_keys[piece_moving][sq_to] ^
                         piece_keys[piece_captured][sq_to];

        break;

    case MOVE_TYPE_QUEEN:
        pos->type_of_pieces[QUEEN] ^= (sq_from_bb | sq_to_bb);
        pos->board[sq_to] = MAKE_PIECE(QUEEN, us);
        pos->board[sq_from] = EMPTY;

        // Update hash keys
        pos->hash_key ^= piece_keys[piece_moving][sq_from] ^
                         piece_keys[piece_moving][sq_to] ^
                         piece_keys[piece_captured][sq_to];
        break;

    case MOVE_TYPE_KING:
        pos->type_of_pieces[KING] ^= (sq_from_bb | sq_to_bb);
        pos->castling &= ~Castle_Rights_Consts[sq_from];
        pos->board[sq_to] = MAKE_PIECE(KING, us);
        pos->board[sq_from] = EMPTY;

        // Update hash keys
        pos->hash_key ^= piece_keys[piece_moving][sq_from] ^
                         piece_keys[piece_moving][sq_to] ^
                         piece_keys[piece_captured][sq_to];
        break;

    case MOVE_TYPE_PROMOTION_KNIGHT:
        pos->type_of_pieces[PAWN] ^= (sq_from_bb);
        pos->type_of_pieces[KNIGHT] ^= (sq_to_bb);
        int promoted_piece_knight = MAKE_PIECE(KNIGHT, us);
        pos->board[sq_to] = promoted_piece_knight;
        pos->board[sq_from] = EMPTY;

        pos->hash_key ^= piece_keys[piece_moving][sq_from] ^
                         piece_keys[promoted_piece_knight][sq_to] ^
                         piece_keys[piece_captured][sq_to];

        break;

    case MOVE_TYPE_PROMOTION_BISHOP:
        pos->type_of_pieces[PAWN] ^= (sq_from_bb);
        pos->type_of_pieces[BISHOP] ^= (sq_to_bb);
        int promoted_piece_bishop = MAKE_PIECE(BISHOP, us);
        pos->board[sq_to] = promoted_piece_bishop;
        pos->board[sq_from] = EMPTY;
        pos->hash_key ^= piece_keys[piece_moving][sq_from] ^
                         piece_keys[promoted_piece_bishop][sq_to] ^
                         piece_keys[piece_captured][sq_to];
        break;

    case MOVE_TYPE_PROMOTION_ROOK:
        pos->type_of_pieces[PAWN] ^= (sq_from_bb);
        pos->type_of_pieces[ROOK] ^= (sq_to_bb);
        int promoted_piece_rook = MAKE_PIECE(ROOK, us);
        pos->board[sq_to] = promoted_piece_rook;
        pos->board[sq_from] = EMPTY;
        pos->hash_key ^= piece_keys[piece_moving][sq_from] ^
                         piece_keys[promoted_piece_rook][sq_to] ^
                         piece_keys[piece_captured][sq_to];
        break;

    case MOVE_TYPE_PROMOTION_QUEEN:
        pos->type_of_pieces[PAWN] ^= (sq_from_bb);
        pos->type_of_pieces[QUEEN] ^= (sq_to_bb);
        int promoted_piece_queen = MAKE_PIECE(QUEEN, us);
        pos->board[sq_to] = promoted_piece_queen;
        pos->board[sq_from] = EMPTY;
        pos->hash_key ^= piece_keys[piece_moving][sq_from] ^
                         piece_keys[promoted_piece_queen][sq_to] ^
                         piece_keys[piece_captured][sq_to];
        break;

    case MOVE_TYPE_ENPASSANT:
        pos->type_of_pieces[PAWN] ^= sq_from_bb | sq_to_bb | ((sq_to_bb >> 8) << (16 * us));
        pos->occupancy_by_color[enemy] &= ~((sq_to_bb >> 8) << (16 * us));
        pos->board[sq_from] = EMPTY;
        pos->board[sq_to] = MAKE_PIECE(PAWN, us);
        int ep_pawn_sq = (sq_to - 8) + (16 * us);
        pos->board[ep_pawn_sq] = EMPTY;

        // Update hash key
        int piece_ep = MAKE_PIECE(PAWN, enemy);
        pos->hash_key ^= piece_keys[piece_moving][sq_from] ^
                         piece_keys[piece_moving][sq_to] ^
                         piece_keys[piece_captured][sq_to] ^
                         piece_keys[piece_ep][ep_pawn_sq];

        break;

    case MOVE_TYPE_CASTLE_KING_SIDE:
        pos->type_of_pieces[KING] ^= sq_from_bb | sq_to_bb;
        pos->castling &= ~Castle_Rights_Consts[sq_from];
        pos->type_of_pieces[ROOK] ^= Castled_Rook_Files[us][0];
        pos->occupancy_by_color[us] ^= Castled_Rook_Files[us][0];
        pos->board[sq_from] = EMPTY;
        int king_castle_kside = MAKE_PIECE(KING, us);
        int rook_castle_kside = MAKE_PIECE(ROOK, us);
        pos->board[sq_to] = king_castle_kside;
        pos->board[Castled_Rook_Squares[us][2]] = EMPTY;
        pos->board[Castled_Rook_Squares[us][3]] = rook_castle_kside;

        // Update hash key.
        pos->hash_key ^= piece_keys[king_castle_kside][sq_from] ^
                         piece_keys[king_castle_kside][sq_to] ^
                         piece_keys[rook_castle_kside][Castled_Rook_Squares[us][2]] ^
                         piece_keys[rook_castle_kside][Castled_Rook_Squares[us][3]];
        break;

    case MOVE_TYPE_CASTLE_QUEEN_SIDE:
        pos->type_of_pieces[KING] ^= sq_from_bb | sq_to_bb;
        pos->castling &= ~Castle_Rights_Consts[sq_from];
        pos->type_of_pieces[ROOK] ^= Castled_Rook_Files[us][1];
        pos->occupancy_by_color[us] ^= Castled_Rook_Files[us][1];

        pos->board[sq_from] = EMPTY;
        int king_castle_qside = MAKE_PIECE(KING, us);
        int rook_castle_qside = MAKE_PIECE(ROOK, us);
        pos->board[sq_to] = king_castle_qside;

        pos->board[Castled_Rook_Squares[us][0]] = EMPTY;
        pos->board[Castled_Rook_Squares[us][1]] = rook_castle_qside;

        pos->hash_key ^= piece_keys[king_castle_qside][sq_from] ^
                         piece_keys[king_castle_qside][sq_to] ^
                         piece_keys[rook_castle_qside][Castled_Rook_Squares[us][0]] ^
                         piece_keys[rook_castle_qside][Castled_Rook_Squares[us][1]];
        break;

    default:
        break;
    }

    pos->type_of_pieces[EMPTY] = ~(pos->occupancy_by_color[COLOR_WHITE] | pos->occupancy_by_color[COLOR_BLACK]);

    // Update Hash information

    // printf("pieces key before promo: %" PRIu64 "\n", pos->hash_key);
    // switch (type_of_move)
    // {
    // case MOVE_TYPE_ENPASSANT:

    //     int ep_pawn_sq = (sq_to - 8) + (16 * us);
    //     int piece_ep = MAKE_PIECE(PAWN, enemy);
    //     pos->hash_key ^= piece_keys[piece_ep][ep_pawn_sq];
    //     break;

    // case MOVE_TYPE_PROMOTION_QUEEN:
    //     int piece = MAKE_PIECE(pos->board[sq_to], us);
    //     pos->hash_key ^= piece_keys[piece][sq_to];
    //     break;
    // }

    if (old_ep_square != 0)
    {
        pos->hash_key ^= enpassant_keys[old_ep_square];
    }

    if (pos->enpassantSquare != 0)
    {
        int ep_square = PopLSB(pos->enpassantSquare);
        pos->hash_key ^= enpassant_keys[ep_square];
    }

    if (old_castle_rights != pos->castling)
    {
        pos->hash_key ^= castle_keys[old_castle_rights];
        pos->hash_key ^= castle_keys[pos->castling];
    }
}