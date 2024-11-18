#include "position.hpp"

#include <sstream>
#include <iostream>

#include "utilities.hpp"


namespace Chess {

std::ostream& operator<<(std::ostream& os, const Position& p) {
    std::string pieceSymbols = " PNBRQK  pnbrqk";


    os << "\n+---+---+---+---+---+---+---+---+\n"; 
    for(int i = 7; i >= 0; i--) {
        for(int j = 0; j < 8; j++) {
            os << "| " << pieceSymbols[p.pieceOn(8 * i + j)] << " ";
        }
        os << "| " << i + 1 << "\n+---+---+---+---+---+---+---+---+\n"; 
    }
    os << "  a   b   c   d   e   f   g   h\n\n";
    return os;
}

//TODO: parseFen vulnerable to invalid FEN
void Position::parseFen(const std::string& fen) {
    std::string pieceSymbols = " PNBRQK  pnbrqk";

    std::istringstream ss(fen);
    unsigned char token;
    Square sq = SQ_A8;
    size_t index;

    ss >> std::noskipws;

    //piece positions
    for(int i = 0; (ss >> token) && !isspace(token); i++) {
        if(i == 64) error("parseFen", 0);
        if(isdigit(token)) {
            if(token == '9') error("parseFen", 1);
            sq += EAST * (token - '0');
        }
        else if(token == '/') {
            sq += SOUTH * 2;
        }
        else if((index = pieceSymbols.find(token)) != std::string::npos) {
            addPiece(Piece(index), sq);
            ++sq;
            if(token == 'K') kingPos[0] = sq;
            else if(token == 'k') kingPos[1] = sq;
        }
        else error("parseFen", 2, token);
    }

    //color on move
    ss >> token;
    colorOnMove = token == 'w' ? WHITE : BLACK;
    ss >> token;

    //casteling rights
    std::string cr = "KQkq";
    while((ss >> token) && !isspace(token)) {
        if(token == '-') {
            ss >> token;
            break;
        }
        castlingRights[cr.find(token)] = true;
    } 

    //en-passant
    ss >> token;
    if(token == '-') {
        state.enPassant = SQ_NONE;
    }
    else {
        int s = int(token - 'a');
        ss >> token;
        state.enPassant = Square(s + 8 * (token - '1'));
    }
    ss >> token;

    //move count
    int mc = 0;
    while((ss >> token) && !isspace(token)) {
        mc *= 10;
        mc += int(token - '0'); 
    }
    state.moveCount = mc;

    //half move count
    int hmc = 0;
    while((ss >> token) && !isspace(token)) {
        hmc *= 10;
        hmc += int(token - '0'); 
    }
    state.halfMoveCount = mc;
}

std::string Position::fen() const {
    return "";
}

Piece Position::pieceOn(int i) const {
    return board[i];
}

int Position::pieceIndex(Piece p) {
    return 6 * ((p & 8) >> 3) + (p & 7) - 1;
}

void Position::makeMove(const Move& move) {
    Piece piece = board[move.from()];
    removePiece(move.from());
    addPiece(piece, move.to());
    colorOnMove != colorOnMove; 
}

void Position::addPiece(Piece p, Square s) {
    Bitboard mask = 1ull << s;
    pieces[(p & 7) - 1] |= mask;
    colors[p >> 3] |= mask;
    board[s] = p;
    pieceCount[pieceIndex(p)]++;
}

void Position::removePiece(Square s) {
    Piece p = pieceOn(s);
    Bitboard mask = 1ull << s;
    pieces[(p & 7) - 1] ^= mask;
    colors[p >> 3] ^= mask;
    board[s] = NO_PIECE;
    pieceCount[pieceIndex(p)]--;
}

}