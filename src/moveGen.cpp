#include "moveGen.hpp"

#include "bitboard.hpp"


namespace Chess {

template<Color color>
Move* generatePawnMoves(const Position& pos, Move* moveList) {
    Bitboard pawns = pos.getPieces(PAWN, color);

    while(pawns) {
        Square pawn = popLSB(pawns);
        Bitboard attacks = pawnAttacks<color>(pawn);

        while(attacks) {
            Square dest = popLSB(attacks);
            *(moveList++) = Move(pawn, dest);
        }
    }
    
    return moveList;
}

template<PieceType pt>
Move* generateMoves(const Position& pos, Move* moveList, Color color) {
    Bitboard pieces = pos.getPieces(pt, color);
    Bitboard occupancy = pos.getPieces(Color(color ^ 1));

    while(pieces) {
        Square piece = popLSB(pieces);
        Bitboard attacks = getAttacks<pt>(piece, occupancy);

        while(attacks) {
            Square dest = popLSB(attacks);
            *(moveList++) = Move(piece, dest);
        }
    }

    return moveList;
}

Move* generate(const Position& pos, Move* moveList) {
    Color color = pos.getColorOnMove();

    moveList = color ? generatePawnMoves<BLACK>(pos, moveList) 
                     : generatePawnMoves<WHITE>(pos, moveList);
    moveList = generateMoves<KNIGHT>(pos, moveList, color);
    moveList = generateMoves<BISHOP>(pos, moveList, color);
    moveList = generateMoves<ROOK>(pos, moveList, color);
    moveList = generateMoves<QUEEN>(pos, moveList, color);
    moveList = generateMoves<KING>(pos, moveList, color);

    return moveList;
}

}