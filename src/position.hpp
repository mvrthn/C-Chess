#pragma once


#include "types.hpp"

#include <string>


namespace Chess {

#define bitboard unsigned long long

class Position {

public:
    Position() = default;

    void parseFen(const std::string&);
    int pieceOn(int) const;

private:
    void addPiece(Piece, Square);
    int pieceIndex(Piece);
        
    bitboard pieces[PIECE_NB] = {0};
    bitboard colors[SQUARE_NB] = {0};
    Piece board[SQUARE_NB] = {NO_PIECE};
    Color colorOnMove;
    bool castlingRights[4] = {false};
    Square enPassant;
    int moveCount;
    int halfMoveCount;
};

std::ostream& operator<<(std::ostream& os, const Position& p);

}