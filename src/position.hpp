#pragma once


#include "types.hpp"

#include <string>


namespace Chess {

class Position {

public:
    Position() = default;

    void parseFen(const std::string&);
    std::string fen();

    Piece pieceOn(int) const;
    static int pieceIndex(Piece);

private:
    void addPiece(Piece, Square);
    void removePiece(Square);

    Bitboard pieces[PIECE_NB] = {0};
    Bitboard colors[SQUARE_NB] = {0};
    Piece board[SQUARE_NB] = {NO_PIECE};
    int pieceCount[PIECE_NB] = {0};
    Color colorOnMove;
    bool castlingRights[4] = {false};
    Square enPassant;
    int moveCount;
    int halfMoveCount;
};

std::ostream& operator<<(std::ostream& os, const Position& p);

}