#pragma once


#include "position.hpp"
#include "bitboard.hpp"
#include "moveGen.hpp"
#include "types.hpp"


namespace Chess {

constexpr auto StartFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

class Engine {

public:
    Engine();

    void loadFen(std::string fen = StartFen);
    std::string generateFen() const;

    const Position& getPosition() const;
    Color colorOnMove() const;

    bool step(Move);
    
private:
    Position position;
    MoveList moveList;
};

}