#include "moveGen.hpp"

#include "bitboard.hpp"


namespace Chess {

template<Color color>
Move* generatePawnMoves(const Position& pos, Move* moveList, Bitboard target) {
    Bitboard pawns = pos.getPieces(PAWN, color);
    Bitboard free = ~pos.getPieces();
    Bitboard enemy = pos.getPieces(~color);
    Bitboard rank3rd = color == WHITE ? Rank3_BB : Rank6_BB;
    Bitboard rank7th = color == WHITE ? Rank7_BB : Rank2_BB;
    constexpr Direction up = color == WHITE ? NORTH : SOUTH;

    Bitboard moved = shift<up>(pawns & ~rank7th) & free;
    Bitboard doubleMoved = shift<up>(moved & rank3rd) & free;

    if(pos.checkers()) {
        moved &= target;
        doubleMoved &= target;
    }

    while(moved) {
        Square dest = popLSB(moved);
        *(moveList++) = Move(dest - up, dest);
    }

    while(doubleMoved) {
        Square dest = popLSB(doubleMoved);
        *(moveList++) = Move(dest - 2 * up, dest);
    }

    while(pawns) {
        Square pawn = popLSB(pawns);
        Bitboard attacks = pawnAttacks<color>(pawn) & enemy;

        while(attacks) {
            Square dest = popLSB(attacks);
            *(moveList++) = Move(pawn, dest);
        }
    }
    
    return moveList;
}

template<PieceType pt>
Move* generateMoves(const Position& pos, Move* moveList, Color color, Bitboard target) {
    Bitboard pieces = pos.getPieces(pt, color);
    Bitboard occupancy = pos.getPieces();

    while(pieces) {
        Square piece = popLSB(pieces);
        Bitboard attacks = getAttacks<pt>(piece, occupancy) & target;

        while(attacks) {
            Square dest = popLSB(attacks);
            *(moveList++) = Move(piece, dest);
        }
    }

    return moveList;
}

Move* generate(const Position& pos, Move* moveList) {
    Color color = pos.getColorOnMove();
    Bitboard notAlly = ~pos.getPieces(color);
    const Square king = lsb(pos.getPieces(KING, color));
    Bitboard checkers = pos.checkers();
    Bitboard target;

    if(!plural(checkers)) {
        
        target = checkers ? between(king, lsb(checkers)) : notAlly;

        moveList = color ? generatePawnMoves<BLACK>(pos, moveList, target) 
                        : generatePawnMoves<WHITE>(pos, moveList, target);
        moveList = generateMoves<KNIGHT>(pos, moveList, color, target);
        moveList = generateMoves<BISHOP>(pos, moveList, color, target);
        moveList = generateMoves<ROOK>(pos, moveList, color, target);
        moveList = generateMoves<QUEEN>(pos, moveList, color, target);
    }

    Bitboard inCheck = 0;
    while(checkers) 
        inCheck |= between(king, popLSB(checkers));
    moveList = generateMoves<KING>(pos, moveList, color, ~inCheck & notAlly);

    return moveList;
}

}