#pragma once


#include "types.hpp"


namespace Chess {

struct BBTable {
    BBTable();
    ~BBTable() = default;

    Bitboard PseudoAttacks[PIECE_TYPE_NB - 1][SQUARE_NB];
    Bitboard PawnAttacks[COLOR_NB][SQUARE_NB];
    Bitboard Lines[SQUARE_NB][SQUARE_NB];
    Bitboard SquaresBetween[SQUARE_NB][SQUARE_NB];
};

constexpr Bitboard FileA = 0x0101010101010101; 
constexpr Bitboard FileB = FileA << 1;  
constexpr Bitboard FileC = FileA << 2;  
constexpr Bitboard FileD = FileA << 3;  
constexpr Bitboard FileE = FileA << 4;  
constexpr Bitboard FileF = FileA << 5;  
constexpr Bitboard FileG = FileA << 6;  
constexpr Bitboard FileH = FileA << 7;

constexpr Bitboard Rank1 = 0xFF;
constexpr Bitboard Rank2 = Rank1 << 0x8;
constexpr Bitboard Rank3 = Rank1 << 0x10;
constexpr Bitboard Rank4 = Rank1 << 0x18;
constexpr Bitboard Rank5 = Rank1 << 0x20;
constexpr Bitboard Rank6 = Rank1 << 0x28;
constexpr Bitboard Rank7 = Rank1 << 0x30;
constexpr Bitboard Rank8 = Rank1 << 0x38;

template<Direction D>
constexpr Bitboard shift(Bitboard b) {
    return D == NORTH         ? b << 8
         : D == SOUTH         ? b >> 8
         : D == NORTH + NORTH ? b << 16
         : D == SOUTH + SOUTH ? b >> 16
         : D == EAST          ? (b & ~FileH) << 1
         : D == WEST          ? (b & ~FileA) >> 1
         : D == NORTH_EAST    ? (b & ~FileH) << 9
         : D == NORTH_WEST    ? (b & ~FileA) << 7
         : D == SOUTH_EAST    ? (b & ~FileH) >> 7
         : D == SOUTH_WEST    ? (b & ~FileA) >> 9
                              : 0;
}

template<Color C>
constexpr Bitboard getPawnAttacks(Bitboard b) {
    return C == WHITE ? shift<NORTH_WEST>(b) | shift<NORTH_EAST>(b)
                      : shift<SOUTH_WEST>(b) | shift<SOUTH_EAST>(b);
}

constexpr Bitboard squareBB(Square s) { return 1ULL << s; }

bool validStep(Square s, int step);

}