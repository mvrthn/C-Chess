#pragma once


#include "types.hpp"
#include <bit>
#include <cassert>


namespace Chess {

struct Magic {
    Bitboard* attacks;
    Bitboard mask;
    Bitboard magic;
    int shift;

    inline unsigned int index(Bitboard occ) {
        unsigned lo = unsigned(occ) & unsigned(mask);
        unsigned hi = unsigned(occ >> 32) & unsigned(mask >> 32);
        return (lo * unsigned(magic) ^ hi * unsigned(magic >> 32)) >> (shift - 32);
    }

    inline Bitboard get(Bitboard occ) {
        return attacks[index(occ)];
    }
};

namespace BBTable {
    void init();
    void initMagics();

    extern Bitboard PseudoAttacks[PIECE_TYPE_NB - 1][SQUARE_NB];
    extern Bitboard PawnAttacks[COLOR_NB][SQUARE_NB];
    extern Bitboard Lines[SQUARE_NB][SQUARE_NB];
    extern Bitboard SquaresBetween[SQUARE_NB][SQUARE_NB];

    extern Bitboard RookAttacks[0x19000];
    extern Bitboard BishopAttacks[0x1480];

    extern Magic RookMagics[SQUARE_NB];
    extern Magic BishopMagics[SQUARE_NB];

    extern uint8_t BitIndex[SQUARE_NB];
};

constexpr Bitboard FileA_BB = 0x0101010101010101; 
constexpr Bitboard FileB_BB = FileA_BB << 1;  
constexpr Bitboard FileC_BB = FileA_BB << 2;  
constexpr Bitboard FileD_BB = FileA_BB << 3;  
constexpr Bitboard FileE_BB = FileA_BB << 4;  
constexpr Bitboard FileF_BB = FileA_BB << 5;  
constexpr Bitboard FileG_BB = FileA_BB << 6;  
constexpr Bitboard FileH_BB = FileA_BB << 7;

constexpr Bitboard Rank1_BB = 0xFF;
constexpr Bitboard Rank2_BB = Rank1_BB << 0x8;
constexpr Bitboard Rank3_BB = Rank1_BB << 0x10;
constexpr Bitboard Rank4_BB = Rank1_BB << 0x18;
constexpr Bitboard Rank5_BB = Rank1_BB << 0x20;
constexpr Bitboard Rank6_BB = Rank1_BB << 0x28;
constexpr Bitboard Rank7_BB = Rank1_BB << 0x30;
constexpr Bitboard Rank8_BB = Rank1_BB << 0x38;

template<Direction D>
constexpr Bitboard shift(Bitboard b) {
    return D == NORTH         ? b << 8
         : D == SOUTH         ? b >> 8
         : D == NORTH + NORTH ? b << 16
         : D == SOUTH + SOUTH ? b >> 16
         : D == EAST          ? (b & ~FileH_BB) << 1
         : D == WEST          ? (b & ~FileA_BB) >> 1
         : D == NORTH_EAST    ? (b & ~FileH_BB) << 9
         : D == NORTH_WEST    ? (b & ~FileA_BB) << 7
         : D == SOUTH_EAST    ? (b & ~FileH_BB) >> 7
         : D == SOUTH_WEST    ? (b & ~FileA_BB) >> 9
                              : 0;
}

constexpr Bitboard squareBB(Square s) { return 1ULL << s; }

constexpr Bitboard rankBB(Square s) { return Rank1_BB << (rankOf(s) * 8); }

constexpr Bitboard fileBB(Square s) { return FileA_BB << fileOf(s); }

inline Square popLSB(Bitboard& b) {
    assert(b);
    Bitboard lsb = b & -b;
    b &= ~lsb;
    return Square(BBTable::BitIndex[(lsb * 0x03f79d71b4cb0a89) >> 58]);
}

inline Square lsb(Bitboard b) {
    assert(b);
    return Square(BBTable::BitIndex[((b & -b) * 0x03f79d71b4cb0a89) >> 58]);
}

inline Bitboard between(Square a, Square b) { return BBTable::SquaresBetween[a][b]; };

inline int popCount(Bitboard b) { return std::__popcount(b); }

inline bool plural(Bitboard b) { return b & (b - 1); }

template<Color color>
inline Bitboard pawnAttacks(Square sq) { return BBTable::PawnAttacks[color][sq]; } 

template<PieceType pt>
inline Bitboard getAttacks(Square sq, Bitboard occ) {
    if(pt == KNIGHT) return BBTable::PseudoAttacks[KNIGHT - 1][sq];
    if(pt == BISHOP) return BBTable::BishopMagics[sq].get(occ);
    if(pt == ROOK) return BBTable::RookMagics[sq].get(occ);
    if(pt == QUEEN) return BBTable::BishopMagics[sq].get(occ) | BBTable::RookMagics[sq].get(occ);
    if(pt == KING) return BBTable::PseudoAttacks[KING - 1][sq];
    return 0;
}

}