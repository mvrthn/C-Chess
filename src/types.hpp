#pragma once


namespace Chess {

enum Color {
    WHITE,
    BLACK,
    COLOR_NB = 2
};

enum Piece {
    NO_PIECE,
    W_PAWN = 1, W_KNIGHT, W_BISHOP, W_ROOK, W_QUEEN, W_KING,
    B_PAWN = 9, B_KNIGHT, B_BISHOP, B_ROOK, B_QUEEN, B_KING,
    PIECE_NB = 12
};

enum Square : int {
    A1, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8,
    NONE,
    SQUARE_NB = 64
};

enum Direction : int {
    RIGHT = 1,
    UP = 8,
    LEFT = -RIGHT,
    DOWN = -UP
};

inline Square& operator++(Square& s) { return s = Square(int(s) + 1); }
inline Square& operator--(Square& s) { return s = Square(int(s) - 1); }

constexpr Direction operator+(Direction d, int i) { return Direction(i + int(d)); }
constexpr Direction operator*(Direction d, int i) { return Direction(i * int(d)); }

constexpr Square operator+(Square s, Direction d) { return Square(int(s) + int(d)); }
constexpr Square operator-(Square s, Direction d) { return Square(int(s) - int(d)); }

inline Square& operator+=(Square& s, Direction d) { return s = s + d; } 
inline Square& operator-=(Square& s, Direction d) { return s = s - d; } 

}