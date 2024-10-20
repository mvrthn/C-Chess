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
            attacks |= squareBB(s);
            if(occupied & squareBB(s)) break;
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
            if(PseudoAttacks[pt - 1][s1] & squareBB(s2)) {
                Lines[s1][s2] = PseudoAttacks[pt - 1][s1] & PseudoAttacks[pt - 1][s2] | squareBB(s1) | squareBB(s2);
                SquaresBetween[s1][s2] = slidingAttack(pt, s1, squareBB(s2)) & 
                                         slidingAttack(pt, s2, squareBB(s1));
            }
            SquaresBetween[s1][s2] |= squareBB(s2);
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
    for(Square s = SQ_A1; s <= SQ_H8; ++s) {
        BitIndex[s] = index64[s];
    } 

}

void BBTable::initMagics() {
    Bitboard pregenMagics[2][64] = {
        { 0x208b110800400102, 0x8451008c02925401, 0x00a8004080641104, 0x0828241004024089, 
          0x0801818c01051040, 0x4818084111408820, 0x02c4285800024202, 0x0801841000220882, 
          0x04010c8018800410, 0x0404044020a20809, 0xa180900002182128, 0x00204254118c4443, 
          0x0802803010008602, 0x94400480004210a8, 0x040c04000044e504, 0x0921a01000442969, 
          0x2439120100400020, 0x840b840200100402, 0x0404000884020204, 0x0411220024113048, 
          0xd025000000888004, 0x4422020208003205, 0x120924018000a082, 0x120924018000a082, 
          0x042c02c0104a2002, 0x042c02c0104a2002, 0x0408013248003800, 0x08220020c0281048, 
          0x0100408880050050, 0x2370040882480882, 0x0882100000248042, 0x004104021280c200, 
          0x0840020108280908, 0x20d0140040010120, 0x0d02080900092821, 0x0008205400200401, 
          0x0200404200080104, 0x00504803240b0202, 0x00504803240b0202, 0x04c200888a128841, 
          0x400164004000a404, 0x8914044040060825, 0x1800240020001218, 0x0400808180000207, 
          0x0080210408000112, 0x0300009000010110, 0x1201542100030206, 0x02c0210041041a84, 
          0xa08c044048004608, 0x0a03400c01019404, 0x8090000017408042, 0x0488100094800003, 
          0x4202808004844151, 0x08088a0250000820, 0x0401022c00088214, 0x0242812a00030e08, 
          0x011423008009a401, 0x81082208002804a9, 0x4480d01000080c01, 0x0109c80010500a00, 
          0x300208800008aa04, 0x30262080004d0040, 0x011132422028400c, 0x0805004046624101 
        },
        { 0xa008820000101040, 0x1002400040080424, 0x01200440a020108a, 0x820c109104100008, 
          0x0210052012000882, 0x0071400462020802, 0x02010a0000820081, 0x0004428080801023, 
          0x2822a01000c08040, 0x064110a200404060, 0x0580104202210020, 0x1080082844808010, 
          0x0220144048402201, 0x0002008880008004, 0x0804010040508102, 0x0720448090008081, 
          0x0040442002008480, 0xc020040a12480010, 0x34c4290000900020, 0x0800500080806202, 
          0x0c21480080a80404, 0x0852002800012404, 0x4010492284020402, 0x1005840440000201, 
          0xc118822000004422, 0x0038c40000010081, 0x4024010000095011, 0x4a18210014801001, 
          0x00204e0000009006, 0x082a001000020442, 0x0204820050190009, 0x0405005100200082, 
          0x0040400000800021, 0x2010200184080410, 0x1010110492002402, 0x0101002028000810, 
          0x0900041a80090801, 0x5080820005400204, 0x1081020000680401, 0xa080008018000141, 
          0x8040400026009028, 0x4110201004013008, 0x101300400c008060, 0x1030100000121401, 
          0x0103001040000408, 0x808500020001000c, 0x030080800006050e, 0x20500818000100e1, 
          0x00800080004860d0, 0x006002804900a440, 0x01084d0010001120, 0x0010088000808048, 
          0x0c0c0a0000512412, 0x0004008100008412, 0x0006010040000451, 0x2080830010040049, 
          0x0020850200244012, 0x0020850200244012, 0x0048200101821029, 0x8490000904087005, 
          0x044409b200402102, 0x0104005980040843, 0x402422c101250002, 0x0004822100080843
        } };

    Bitboard edge;
    int bSize = 0, rSize = 0;

    for(Square sq = SQ_A1; sq <= SQ_H8; ++sq) {
        edge = ((Rank1_BB | Rank8_BB) & ~rankBB(sq)) | ((FileA_BB | FileH_BB) & ~fileBB(sq)); 

        Magic& bm = BishopMagics[sq];
        Magic& rm = RookMagics[sq];

        bm.mask = slidingAttack(BISHOP, sq, 0) & ~edge;
        rm.mask = slidingAttack(ROOK, sq, 0) & ~edge;

        bm.shift = 64 - popCount(bm.mask);
        rm.shift = 64 - popCount(rm.mask);

        bm.magic = pregenMagics[0][sq];
        rm.magic = pregenMagics[1][sq];

        bm.attacks = sq == SQ_A1 ? BishopAttacks : BishopMagics[sq - 1].attacks + bSize;
        rm.attacks = sq == SQ_A1 ? RookAttacks : RookMagics[sq - 1].attacks + rSize;

        Bitboard b = 0;
        bSize = 0, rSize = 0;
        do {
            bm.attacks[bm.index(b)] = slidingAttack(BISHOP, sq, b);

            bSize++;
            b = (b - bm.mask) & bm.mask;
        } while(b);
        
        b = 0;
        do {
            rm.attacks[rm.index(b)] = slidingAttack(ROOK, sq, b);

            rSize++;
            b = (b - rm.mask) & rm.mask;
        } while(b);
    }
}

}