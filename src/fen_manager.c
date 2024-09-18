#include "castling_permissions.h"
#include "color.h"
#include "direction.h"
#include "fen_manager.h"
#include "pieces.h"
#include "position.h"
#include "squares.h"
#include "utilities.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "zobrist.h"
#include "transposition_table.h"

// Set the board as per the pieces and update the pieces and occupancy_by_color bitboards better.
void SetBoard(char *fen, Position *pos)
{
    char *ptr = fen;
    int sq = SQ_A8;

    while (*ptr && *ptr != ' ' && *ptr != '\n')
    {
        if (isdigit(*ptr))
        {
            sq += (*ptr - '0') * EAST; // Advance the given number of files
        }
        else if (*ptr == '/')
        {
            sq += (2 * SOUTH); // Move to the next rank
        }
        else
        {
            // Parse piece
            int piece = index_of(PIECES_STR, *ptr);
            pos->board[sq] = piece;
            sq++;
        }
        ptr++;
    }
}

void UpdateBitBoards(Position *pos)
{

    for (int sq = SQ_A1; sq <= SQ_H8; sq++)
    {
        int typeOfpiece = TYPE_OF_PIECE(pos->board[sq]);
        pos->type_of_pieces[typeOfpiece] |= (1ULL << sq);
        if (typeOfpiece != EMPTY)
        {
            int colorOfPiece = COLOR_OF_PIECE(pos->board[sq]);
            pos->occupancy_by_color[colorOfPiece] |= (1ULL << sq);
        }
    }
}
// Clear the board.
void ClearBoard(Position *pos)
{
    for (int sq = SQ_A1; sq <= SQ_H8; sq++)
    {
        pos->board[sq] = EMPTY;
    }
    for (int piece = EMPTY; piece <= KING; piece++)
    {
        pos->type_of_pieces[piece] = 0ULL;
    }

    for (int color = COLOR_WHITE; color <= COLOR_BLACK; color++)
    {
        pos->occupancy_by_color[color] = 0ULL;
    }

    pos->sideToMove = -1;

    pos->castling = NO_CASTLING;

    pos->enpassantSquare = SQ_NONE_BB;
    pos->halfMoves = 0;
    pos->fullMoves = 0;
}

// Sets the side to move from fen.
void SetSideToMove(char *fen, Position *pos)
{
    char *ptr = fen;
    find_next_space(ptr, &ptr);
    pos->sideToMove = (*ptr == 'w') ? COLOR_WHITE : COLOR_BLACK;
}

// Sets the castling rights from fen.
void SetCastlingRights(char *fen, Position *pos)
{
    char *ptr = fen;
    for (int i = 0; i < 2; i++)
    {
        find_next_space(ptr, &ptr);
    }

    // Parse castling rights
    while (*ptr && *ptr != ' ' && *ptr != '\n')
    {
        if (*ptr == 'K')
        {
            pos->castling |= WHITE_KINGSIDE_CASTLE;
        }
        else if (*ptr == 'Q')
        {
            pos->castling |= WHITE_QUEENSIDE_CASTLE;
        }
        else if (*ptr == 'k')
        {
            pos->castling |= BLACK_KINGSIDE_CASTLE;
        }
        else if (*ptr == 'q')
        {
            pos->castling |= BLACK_QUEENSIDE_CASTLE;
        }
        else if (*ptr == '-')
        {
            // No castling rights for this side
            break;
        }

        ++ptr;
    }
}

// Set the enpassant square from fen.
void SetEnPassantSquare(char *fen, Position *pos)
{
    char *ptr = fen;
    for (int i = 0; i < 3; i++)
    {
        find_next_space(ptr, &ptr);
    }
    // Parse en passant square
    if (*ptr != '-')
    {
        // En passant square specified in the FEN string
        int file = *ptr - 'a';       // File is the character itself minus 'a'
        int rank = *(ptr + 1) - '1'; // Rank is the character itself minus '1'
        pos->enpassantSquare = 1ULL << (file + 8 * rank);
    }
    else
    {
        // No en passant square specified
        pos->enpassantSquare = SQ_NONE_BB;
    }
}

// Set half move
void SetHalfMoveNumber(char *fen, Position *pos)
{
    char *ptr = fen;
    for (int i = 0; i < 4; i++)
    {
        find_next_space(ptr, &ptr);
    }
    // Parse halfmove clock
    pos->halfMoves = 0;
    while (*ptr && *ptr != ' ')
    {
        if (isdigit(*ptr))
        {
            pos->halfMoves = 10 * pos->halfMoves + (*ptr - '0');
        }
        else if (*ptr == ' ')
        {
            break;
        }
        ++ptr;
    }
}

// Set full move number
void SetFullMoveNumber(char *fen, Position *pos)
{
    char *ptr = fen;

    for (int i = 0; i < 5; i++)
    {
        find_next_space(ptr, &ptr);
    }
    // Parse fullmove number
    pos->fullMoves = 0;
    while (*ptr)
    {
        if (isdigit(*ptr))
        {
            pos->fullMoves = 10 * pos->fullMoves + (*ptr - '0');
        }
        else if (*ptr == ' ')
        {
            break;
        }
        ++ptr;
    }
}

// Method to set the state of the position as per fen.
void set_board_from_fen(char *fen, Position *pos)
{
    ClearBoard(pos);
    SetBoard(fen, pos);
    UpdateBitBoards(pos);
    SetSideToMove(fen, pos);
    SetCastlingRights(fen, pos);
    SetEnPassantSquare(fen, pos);
    SetHalfMoveNumber(fen, pos);
    SetFullMoveNumber(fen, pos);
    pos->hash_key = generate_hash_key_from_scratch(pos);
    RepetitionTable[0] = pos->hash_key;
    // for (int p = EMPTY; p <= KING; p++)
    // {
    //     printf("%d -> %lu\n", p, pos->type_of_pieces[p]);
    // }

    // printf("White BB - %lu\n", pos->occupancy_by_color[COLOR_WHITE]);
    // printf("BLACK BB - %lu\n", pos->occupancy_by_color[COLOR_BLACK]);
    // printf("Turn - %d\n", pos->sideToMove);
    // printf("Castling - %d\n", pos->castling);
    // printf("enpass - %lu\n", pos->enpassantSquare);
    // printf("half - %d\n", pos->halfMoves);
    // printf("full - %d\n", pos->fullMoves);
}
