#include "bitboard.hpp"


#include <initializer_list>
#include <cmath>
#include <cassert>

#include "types.hpp"


namespace Chess {

bool validStep(Square s, int step) {
    Square dest = Square(s + step);
    if(!squareInBound(dest)) return false;
    if(std::abs(rankOf(s) - rankOf(dest)) > 2 || 
       std::abs(fileOf(s) - fileOf(dest)) > 2) return false; 
    return true; 
}

Bitboard slidingAttack(PieceType pt, Square sq, Bitboard occupied) {
    Bitboard attacks = 0;
    Direction rookDir[4] = {NORTH, EAST, SOUTH, WEST}; 
    Direction bishopDir[4] = {NORTH_EAST, SOUTH_EAST, SOUTH_WEST, NORTH_WEST};

    for(auto d : pt == ROOK ? rookDir : bishopDir) {
        Square s = sq;
        while(validStep(s, d)) {
            s += d;
            attacks |= s;
            if(occupied & s) break;
        }
    }

    return attacks;
}

BBTable::BBTable() {

    for(Square s = SQ_A1; s <= SQ_H8; ++s) {
        PawnAttacks[WHITE][s] = getPawnAttacks<WHITE>(squareBB(s));
        PawnAttacks[BLACK][s] = getPawnAttacks<BLACK>(squareBB(s));

        for(int step : {-17, -15, -10, -6, 6, 10, 15, 17}) {
            if(!validStep(s, step)) continue;
            PseudoAttacks[KNIGHT - 1][s] |= squareBB(s + step);
        }

        for(int step : {-9, -8, -7, -1, 1, 7, 8, 9}) {
            if(!validStep(s, step)) continue;
            PseudoAttacks[KING - 1][s] |= squareBB(s + step);
        }

        PseudoAttacks[BISHOP - 1][s] = slidingAttack(BISHOP, s, 0);
        PseudoAttacks[ROOK - 1][s] = slidingAttack(ROOK, s, 0);

        PseudoAttacks[QUEEN - 1][s] = PseudoAttacks[BISHOP - 1][s] | PseudoAttacks[ROOK - 1][s];
    }

    for(Square s1 = SQ_A1; s1 <= SQ_H8; ++s1) {
        for(Square s2 = SQ_A1; s2 <= SQ_H8; ++s2)
        for(PieceType pt : {BISHOP, ROOK}) {
            if(PseudoAttacks[pt - 1][s1] & s2) {
                Lines[s1][s2] = PseudoAttacks[pt - 1][s1] & PseudoAttacks[pt - 1][s2] | s1 | s2;
                SquaresBetween[s1][s2] = slidingAttack(pt, s1, squareBB(s2)) & 
                                         slidingAttack(pt, s2, squareBB(s1));
            }
            SquaresBetween[s1][s2] |= s2;
        }
    }
}

}