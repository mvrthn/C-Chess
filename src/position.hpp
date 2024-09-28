#pragma once


#include "types.hpp"

#include <string>


namespace Chess {

struct State {
    Bitboard checkers;
    Square enPassant;
    int moveCount;
    int halfMoveCount;
};

class Position {

public:
    Position() = default;

    void parseFen(const std::string&);
    std::string fen() const;

    Piece pieceOn(int) const;
    static int pieceIndex(Piece);

    inline Bitboard checkers() const { return state.checkers; };

private:
    void addPiece(Piece, Square);
    void removePiece(Square);

    Bitboard pieces[PIECE_NB] = {0};
    Bitboard colors[COLOR_NB] = {0};
    Piece board[SQUARE_NB] = {NO_PIECE};
    int pieceCount[PIECE_NB] = {0};
    Color colorOnMove;
    bool castlingRights[4] = {false};
    State state;
};

std::ostream& operator<<(std::ostream& os, const Position& p);

}