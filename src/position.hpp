#pragma once


#include "types.hpp"

#include <string>


namespace Chess {

struct State {
    Bitboard checkers = 0ULL;
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

    inline Color getColorOnMove() const { return colorOnMove; };
    inline Bitboard checkers() const { return state.checkers; };

    inline Bitboard getPieces(PieceType pt, Color color) const { return pieces[pt] & colors[color]; };
    inline Bitboard getPieces(PieceType pt) const { return pieces[pt]; };
    inline Bitboard getPieces(Color color) const;
    inline Bitboard getPieces() const;

    void makeMove(const Move&);

private:
    void addPiece(Piece, Square);
    void removePiece(Square);

    void generateCheckers();

    Bitboard pieces[PIECE_TYPE_NB] = {0ULL};
    Bitboard colors[COLOR_NB] = {0ULL};
    Piece board[SQUARE_NB] = {NO_PIECE};
    int pieceCount[PIECE_NB] = {0ULL};
    Color colorOnMove;
    bool castlingRights[4] = {false};
    State state;
};

inline Bitboard Position::getPieces(Color color) const {
    return (pieces[PAWN] | pieces[KNIGHT] | pieces[BISHOP] | 
            pieces[ROOK] | pieces[QUEEN] | pieces[KING]) & colors[color];
}

inline Bitboard Position::getPieces() const {
    return pieces[PAWN] | pieces[KNIGHT] | pieces[BISHOP] | 
           pieces[ROOK] | pieces[QUEEN] | pieces[KING];
}

std::ostream& operator<<(std::ostream& os, const Position& p);

}