#include "bitboard.hpp"


#include <initializer_list>
#include <cmath>
#include <cassert>

#include "types.hpp"
#include "utilities.hpp"


namespace Chess {

namespace BBTable {

Bitboard PseudoAttacks[PIECE_TYPE_NB - 1][SQUARE_NB];
Bitboard PawnAttacks[COLOR_NB][SQUARE_NB];
Bitboard Lines[SQUARE_NB][SQUARE_NB];
Bitboard SquaresBetween[SQUARE_NB][SQUARE_NB];

Bitboard RookAttacks[0x19000];
Bitboard BishopAttacks[0x1480];

Magic RookMagics[SQUARE_NB];
Magic BishopMagics[SQUARE_NB];

uint8_t BitIndex[SQUARE_NB];

}

bool validStep(Square s, int step) {
    Square dest = Square(s + step);
    if(!squareInBound(dest)) return false;
    if(std::abs(rankOf(s) - rankOf(dest)) > 2 || 
       std::abs(fileOf(s) - fileOf(dest)) > 2) return false; 
    return true; 
}

template<Color C>
constexpr Bitboard getPawnAttacks(Bitboard b) {
    return C == WHITE ? shift<NORTH_WEST>(b) | shift<NORTH_EAST>(b)
                      : shift<SOUTH_WEST>(b) | shift<SOUTH_EAST>(b);
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

void BBTable::init() {

    initMagics();

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

        PseudoAttacks[BISHOP - 1][s] = getAttacks<BISHOP>(s, 0);
        PseudoAttacks[ROOK - 1][s] = getAttacks<ROOK>(s, 0);

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
    
    uint8_t index64[SQUARE_NB] = {
         0,  1, 48,  2, 57, 49, 28,  3,
         61, 58, 50, 42, 38, 29, 17,  4,
         62, 55, 59, 36, 53, 51, 43, 22,
         45, 39, 33, 30, 24, 18, 12,  5,
         63, 47, 56, 27, 60, 41, 37, 16,
         54, 35, 52, 21, 44, 32, 23, 11,
         46, 26, 40, 15, 34, 20, 31, 10,
         25, 14, 19,  9, 13,  8,  7,  6 
        };
    for(int i = 0; i < SQUARE_NB; i++) {
        BitIndex[i] = index64[i];
    } 

}

void BBTable::initMagics() {
    Bitboard pregenMagics[2][64] = {
        { 0x31010a0044021521, 0x0080200710301002, 0x4221080080049122, 0x1000124640080581,
          0x84084410001450c0, 0x900808020a060104, 0x0848401c04c0d808, 0x01100a40c3808528,
          0x4801304440803027, 0x024081202006901b, 0x8606120002000401, 0x0880102091a82404,
          0x1040002a20030a32, 0x44201a0160021091, 0x1008080104402244, 0x0182203100450909,
          0x12100c4302280010, 0x9a58410212580017, 0x0142058800102009, 0x0620a00400008104,
          0x0301148200010002, 0x8900900800204026, 0x0105200108024202, 0x00420a0410804092,
          0x4802086023601201, 0x1811040840b00600, 0x0900c20004031000, 0x2010201840004400,
          0x0080805008101440, 0x0080a00c11006100, 0x0424010600114904, 0x0424010600114904,
          0x1220200802021804, 0x0814040000015102, 0x0006c10180040c04, 0x401880a000000208,
          0x0812480883820042, 0x0080808025149011, 0x0006c10180040c04, 0x0101c2007000812a,
          0x2402120200880202, 0x0863244230004108, 0x0120820000114108, 0x2090110022400099,
          0x1410020240000202, 0xb040822001411001, 0x020031000204012a, 0x81420500109001c1,
          0x0828000078040105, 0x0402063624084424, 0x40b0000124240049, 0x504400000c040252,
          0x020a050102880092, 0x100220000130a004, 0x008108540051302b, 0x708028a2008d1044,
          0x10940401000a0101, 0x0118244024002821, 0x8406062000441221, 0x020a020000030108,
          0x10020225200102a0, 0x02c6220020400120, 0x080e910800104144, 0x50c200800a982129 
        },
        { 0x1100400000808020, 0x1100400000808020, 0x00200a10e0800890, 0x010a00c000800410,
          0x9080084080810404, 0x04081a0481000201, 0x48600480102008a1, 0x8201228080801249,
          0x0100500000440204, 0x1020031000200804, 0x2010802000082008, 0x2010802000082008,
          0x20500806801a0022, 0x20500806801a0022, 0x038421000a008022, 0x0108442002200811,
          0x8002c02009010202, 0x2041200441100040, 0x2400300100004420, 0x0400090210004042,
          0x0580100800080102, 0x03100c0020020202, 0x0005020048820101, 0x2491040100000201,
          0x1080010200424021, 0x3042050080908022, 0x004820802c020212, 0x1010006420000921,
          0x58cc050008229801, 0x0014400200408901, 0xc008104230680104, 0x0d00048201380041,
          0x0040105040900823, 0x0040105040900823, 0x0080220600008610, 0x0080502010008289,
          0x1640040011120008, 0x0080048000a41102, 0x0040010000028c4a, 0x0081004000009601,
          0x0020800000049050, 0x2020200802409009, 0x0184202200080441, 0x0821000800210010,
          0x0302040201006208, 0x0400402220054302, 0x004020808200e001, 0x0400404030110081,
          0x0040302000900080, 0x60108080c0086941, 0x041010200c002106, 0x801180800810400a,
          0x041010200c002106, 0x0890c80401002004, 0x11b0201000104082, 0x0180028090800871,
          0x0280006104304013, 0x00a1405140040221, 0x2011482520086005, 0x0404405290881822,
          0x12508c220a640482, 0x0818211260000402, 0x0012008104000a85, 0x20009023018000c1
        } };

    Bitboard edge;
    int bSize = 0, rSize = 0;

    for(Square sq = SQ_A1; sq <= SQ_H8; ++sq) {
        edge = ((Rank1_BB | Rank8_BB) & ~rankBB(sq)) | ((FileA_BB | FileB_BB) & ~fileBB(sq)); 

        Magic& bm = BishopMagics[sq];
        Magic& rm = RookMagics[sq];

        bm.mask = slidingAttack(BISHOP, sq, 0);
        rm.mask = slidingAttack(ROOK, sq, 0);

        bm.shift = 64 - popCount(bm.mask);
        rm.shift = 64 - popCount(rm.mask);

        bm.magic = pregenMagics[0][sq];
        rm.magic = pregenMagics[1][sq];

        bm.attacks = sq == SQ_A1 ? BishopAttacks : BishopMagics[sq - 1].attacks + bSize;
        rm.attacks = sq == SQ_A1 ? RookAttacks : RookMagics[sq - 1].attacks + rSize;

        Bitboard b = 0;
        bSize = 0, rSize = 0;
        do {
            bm.attacks[(b * bm.magic) >> bm.shift] = slidingAttack(BISHOP, sq, b);

            bSize++;
            b = (b - bm.mask) & bm.mask;
        } while(b);
        
        b = 0;
        do {
            rm.attacks[(b * rm.magic) >> rm.shift] = slidingAttack(ROOK, sq, b);

            rSize++;
            b = (b - rm.mask) & rm.mask;
        } while(b);
    }
}

}