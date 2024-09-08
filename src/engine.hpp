#pragma once


#include "position.hpp"
#include "types.hpp"


namespace Chess {

constexpr auto startFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

class Engine {

public:
    Engine() = default;

    void loadFen(std::string fen = startFen);
    std::string generateFen();

    const Position& getPosition();

private:
    Position position;
};

}