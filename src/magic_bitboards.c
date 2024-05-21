#include "magic_bitboards.h"
#include "pieces.h"
#include "squares.h"
#include "utilities.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
// Code taken from chessprogramming wiki.

uint64_t RookTable[0x19000];  // To store rook attacks
uint64_t BishopTable[0x1480]; // To store bishop attacks
Magic RookMagics[64];
Magic BishopMagics[64];

int BitsRequiredByRook[] =
    {
        52, 53, 53, 53, 53, 53, 53, 52,
        53, 54, 54, 54, 54, 54, 54, 53,
        53, 54, 54, 54, 54, 54, 54, 53,
        53, 54, 54, 54, 54, 54, 54, 53,
        53, 54, 54, 54, 54, 54, 54, 53,
        53, 54, 54, 54, 54, 54, 54, 53,
        53, 54, 54, 54, 54, 54, 54, 53,
        52, 53, 53, 53, 53, 53, 53, 52};

int BitsRequiredByBishop[] =
    {
        58, 59, 59, 59, 59, 59, 59, 58,
        59, 59, 59, 59, 59, 59, 59, 59,
        59, 59, 57, 57, 57, 57, 59, 59,
        59, 59, 57, 55, 55, 57, 59, 59,
        59, 59, 57, 55, 55, 57, 59, 59,
        59, 59, 57, 57, 57, 57, 59, 59,
        59, 59, 59, 59, 59, 59, 59, 59,
        58, 59, 59, 59, 59, 59, 59, 58};

const uint64_t RookMagicNumber[64] =
    {
        0x0a8002c000108020ULL, 0x06c00049b0002001ULL, 0x0100200010090040ULL, 0x2480041000800801ULL, 0x0280028004000800ULL, 0x0900410008040022ULL, 0x0280020001001080ULL, 0x2880002041000080ULL,
        0xa000800080400034ULL, 0x0004808020004000ULL, 0x2290802004801000ULL, 0x0411000d00100020ULL, 0x0402800800040080ULL, 0x000b000401004208ULL, 0x2409000100040200ULL, 0x0001002100004082ULL,
        0x0022878001e24000ULL, 0x1090810021004010ULL, 0x0801030040200012ULL, 0x0500808008001000ULL, 0x0a08018014000880ULL, 0x8000808004000200ULL, 0x0201008080010200ULL, 0x0801020000441091ULL,
        0x0000800080204005ULL, 0x1040200040100048ULL, 0x0000120200402082ULL, 0x0d14880480100080ULL, 0x0012040280080080ULL, 0x0100040080020080ULL, 0x9020010080800200ULL, 0x0813241200148449ULL,
        0x0491604001800080ULL, 0x0100401000402001ULL, 0x4820010021001040ULL, 0x0400402202000812ULL, 0x0209009005000802ULL, 0x0810800601800400ULL, 0x4301083214000150ULL, 0x204026458e001401ULL,
        0x0040204000808000ULL, 0x8001008040010020ULL, 0x8410820820420010ULL, 0x1003001000090020ULL, 0x0804040008008080ULL, 0x0012000810020004ULL, 0x1000100200040208ULL, 0x430000a044020001ULL,
        0x0280009023410300ULL, 0x00e0100040002240ULL, 0x0000200100401700ULL, 0x2244100408008080ULL, 0x0008000400801980ULL, 0x0002000810040200ULL, 0x8010100228810400ULL, 0x2000009044210200ULL,
        0x4080008040102101ULL, 0x0040002080411d01ULL, 0x2005524060000901ULL, 0x0502001008400422ULL, 0x489a000810200402ULL, 0x0001004400080a13ULL, 0x4000011008020084ULL, 0x0026002114058042ULL};

const uint64_t BishopMagicNumber[64] =
    {
        0x89a1121896040240ULL, 0x2004844802002010ULL, 0x2068080051921000ULL, 0x62880a0220200808ULL, 0x0004042004000000ULL, 0x0100822020200011ULL, 0xc00444222012000aULL, 0x0028808801216001ULL,
        0x0400492088408100ULL, 0x0201c401040c0084ULL, 0x00840800910a0010ULL, 0x0000082080240060ULL, 0x2000840504006000ULL, 0x30010c4108405004ULL, 0x1008005410080802ULL, 0x8144042209100900ULL,
        0x0208081020014400ULL, 0x004800201208ca00ULL, 0x0f18140408012008ULL, 0x1004002802102001ULL, 0x0841000820080811ULL, 0x0040200200a42008ULL, 0x0000800054042000ULL, 0x88010400410c9000ULL,
        0x0520040470104290ULL, 0x1004040051500081ULL, 0x2002081833080021ULL, 0x000400c00c010142ULL, 0x941408200c002000ULL, 0x0658810000806011ULL, 0x0188071040440a00ULL, 0x4800404002011c00ULL,
        0x0104442040404200ULL, 0x0511080202091021ULL, 0x0004022401120400ULL, 0x80c0040400080120ULL, 0x8040010040820802ULL, 0x0480810700020090ULL, 0x0102008e00040242ULL, 0x0809005202050100ULL,
        0x8002024220104080ULL, 0x0431008804142000ULL, 0x0019001802081400ULL, 0x0200014208040080ULL, 0x3308082008200100ULL, 0x041010500040c020ULL, 0x4012020c04210308ULL, 0x208220a202004080ULL,
        0x0111040120082000ULL, 0x6803040141280a00ULL, 0x2101004202410000ULL, 0x8200000041108022ULL, 0x0000021082088000ULL, 0x0002410204010040ULL, 0x0040100400809000ULL, 0x0822088220820214ULL,
        0x0040808090012004ULL, 0x00910224040218c9ULL, 0x0402814422015008ULL, 0x0090014004842410ULL, 0x0001000042304105ULL, 0x0010008830412a00ULL, 0x2520081090008908ULL, 0x40102000a0a60140ULL
    };

uint64_t GetSlidingAttacksRook(int sq, uint64_t block)
{

    uint64_t result = 0ULL;
    int rk = sq / 8, fl = sq % 8, r, f;
    for (r = rk + 1; r <= 7; r++)
    {
        result |= (1ULL << (fl + r * 8));
        if (block & (1ULL << (fl + r * 8)))
            break;
    }
    for (r = rk - 1; r >= 0; r--)
    {
        result |= (1ULL << (fl + r * 8));
        if (block & (1ULL << (fl + r * 8)))
            break;
    }
    for (f = fl + 1; f <= 7; f++)
    {
        result |= (1ULL << (f + rk * 8));
        if (block & (1ULL << (f + rk * 8)))
            break;
    }
    for (f = fl - 1; f >= 0; f--)
    {
        result |= (1ULL << (f + rk * 8));
        if (block & (1ULL << (f + rk * 8)))
            break;
    }
    return result;
}

// Code taken from chessprogramming wiki.
uint64_t GetSlidingAttacksBishop(int sq, uint64_t block)
{
    uint64_t result = 0ULL;
    int rk = sq / 8, fl = sq % 8, r, f;
    for (r = rk + 1, f = fl + 1; r <= 7 && f <= 7; r++, f++)
    {
        result |= (1ULL << (f + r * 8));
        if (block & (1ULL << (f + r * 8)))
            break;
    }
    for (r = rk + 1, f = fl - 1; r <= 7 && f >= 0; r++, f--)
    {
        result |= (1ULL << (f + r * 8));
        if (block & (1ULL << (f + r * 8)))
            break;
    }
    for (r = rk - 1, f = fl + 1; r >= 0 && f <= 7; r--, f++)
    {
        result |= (1ULL << (f + r * 8));
        if (block & (1ULL << (f + r * 8)))
            break;
    }
    for (r = rk - 1, f = fl - 1; r >= 0 && f >= 0; r--, f--)
    {
        result |= (1ULL << (f + r * 8));
        if (block & (1ULL << (f + r * 8)))
            break;
    }
    return result;
}

// Code is taken from stockfish.
void InitMagics(int pieceType, uint64_t *table, Magic *magics)
{

    uint64_t occupancy[4096], reference[4096], edges, b;
    int epoch[4096] = {}, cnt = 0, size = 0;

    for (int s = SQ_A1; s <= SQ_H8; s++)
    {
        uint64_t rankOfSquare = GetRankFromSquare(s);
        uint64_t currentRankBB = RANK_1_BB << (8ULL * rankOfSquare);
        uint64_t fileOfSquare = GetFileFromSquare(s);
        uint64_t currentFileBB = FILE_A_BB << (fileOfSquare);

        edges = ((RANK_1_BB | RANK_8_BB) & ~currentRankBB) | ((FILE_A_BB | FILE_H_BB) & ~currentFileBB);

        Magic *m = &magics[s];
        m->mask = (pieceType == ROOK ? GetSlidingAttacksRook(s, 0) : GetSlidingAttacksBishop(s, 0)) & ~edges;
        m->shift = (pieceType == ROOK ? BitsRequiredByRook[s] : BitsRequiredByBishop[s]);
        m->attacks = s == SQ_A1 ? table : magics[s - 1].attacks + size;
        b = size = 0;
        do
        {
            occupancy[size] = b;
            reference[size] = pieceType == ROOK ? GetSlidingAttacksRook(s, b) : GetSlidingAttacksBishop(s, b);
            size++;
            b = (b - m->mask) & m->mask;
        } while (b > 0);

        for (int i = 0; i < size;)
        {
            m->magic = (pieceType == ROOK ? RookMagicNumber[s] : BishopMagicNumber[s]);
            for (++cnt, i = 0; i < size; ++i)
            {
                int idx = (((occupancy[i] & m->mask) * m->magic) >> m->shift);

                if (epoch[idx] < cnt)
                {
                    epoch[idx] = cnt;
                    m->attacks[idx] = reference[i];
                }
                else if (m->attacks[idx] != reference[i])
                {

                    break;
                }
            }
        }
    }
}

void InitMagicsAll()
{
    InitMagics(ROOK, RookTable, RookMagics);
    InitMagics(BISHOP, BishopTable, BishopMagics);
}