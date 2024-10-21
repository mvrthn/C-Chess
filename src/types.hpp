#pragma once


#include <cstdint>


namespace Chess {

using Bitboard = uint64_t;

enum Color {
    WHITE,
    BLACK,
    COLOR_NB = 2
};

enum PieceType {
    PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING,
    PIECE_TYPE_NB = 6
};

enum Piece {
    NO_PIECE,
    W_PAWN = 1, W_KNIGHT, W_BISHOP, W_ROOK, W_QUEEN, W_KING,
    B_PAWN = 9, B_KNIGHT, B_BISHOP, B_ROOK, B_QUEEN, B_KING,
    PIECE_NB = 12
};

enum Square : int {
    SQ_A1, SQ_B1, SQ_C1, SQ_D1, SQ_E1, SQ_F1, SQ_G1, SQ_H1,
    SQ_A2, SQ_B2, SQ_C2, SQ_D2, SQ_E2, SQ_F2, SQ_G2, SQ_H2,
    SQ_A3, SQ_B3, SQ_C3, SQ_D3, SQ_E3, SQ_F3, SQ_G3, SQ_H3,
    SQ_A4, SQ_B4, SQ_C4, SQ_D4, SQ_E4, SQ_F4, SQ_G4, SQ_H4,
    SQ_A5, SQ_B5, SQ_C5, SQ_D5, SQ_E5, SQ_F5, SQ_G5, SQ_H5,
    SQ_A6, SQ_B6, SQ_C6, SQ_D6, SQ_E6, SQ_F6, SQ_G6, SQ_H6,
    SQ_A7, SQ_B7, SQ_C7, SQ_D7, SQ_E7, SQ_F7, SQ_G7, SQ_H7,
    SQ_A8, SQ_B8, SQ_C8, SQ_D8, SQ_E8, SQ_F8, SQ_G8, SQ_H8,
    SQ_NONE,
    SQUARE_NB = 64
};

enum File : int {
    FILE_A,
    FILE_B,
    FILE_C,
    FILE_D,
    FILE_E,
    FILE_F,
    FILE_G,
    FILE_H,
    FILE_NB = 8
};

enum Rank : int {
    RANK_1,
    RANK_2,
    RANK_3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8,
    RANK_NB = 8
};

enum Direction : int {
    EAST = 1,
    NORTH = 8,
    WEST = -EAST,
    SOUTH = -NORTH,

    NORTH_EAST = NORTH + EAST,
    NORTH_WEST = NORTH + WEST,
    SOUTH_EAST = SOUTH + EAST,
    SOUTH_WEST = SOUTH + WEST
};

inline Square& operator++(Square& s) { return s = Square(int(s) + 1); }
inline Square& operator--(Square& s) { return s = Square(int(s) - 1); }

constexpr Direction operator+(Direction d, int i) { return Direction(i + int(d)); }
constexpr Direction operator*(Direction d, int i) { return Direction(i * int(d)); }

constexpr Square operator+(Square s, Direction d) { return Square(int(s) + int(d)); }
constexpr Square operator-(Square s, Direction d) { return Square(int(s) - int(d)); }

constexpr Square operator+(Square s, int i) { return Square(int(s) + i); }
constexpr Square operator-(Square s, int i) { return Square(int(s) - i); }

inline Square& operator+=(Square& s, Direction d) { return s = s + d; } 
inline Square& operator-=(Square& s, Direction d) { return s = s - d; } 

constexpr bool squareInBound(Square s) { return s >= SQ_A1 && s <= SQ_H8; }

constexpr File fileOf(Square s) { return File(s & 7); }

constexpr Rank rankOf(Square s) { return Rank(s >> 3); }

constexpr Color operator~(Color c) { return Color(c ^ BLACK); }

enum RenderCond : int {
    NO_RENDER = 0,
    DRAW = 1,
    RENDER_BOARD = 2,
    RENDER_PIECE_SET = 4
};

constexpr RenderCond operator^(RenderCond rc1, RenderCond rc2) { return RenderCond(int(rc1) ^ int(rc2)); }

inline RenderCond& operator^=(RenderCond& rc1, RenderCond rc2) { return rc1 = rc1 ^ rc2; }

enum MoveType {
    STANDARD,
    ENPASSANT,
    CASTELING,
    PROMOTION
};

struct Move {
    Move() = default;
    explicit Move(int64_t d): data(d) {};
    inline Move(Square from, Square to) { data = (from << 6) + to; };

    inline Square from() { return Square(data >> 6); };
    inline Square to() { return Square(data & 0b111111); };

    uint16_t data;
};

}