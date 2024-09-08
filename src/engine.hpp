#pragma once


#include "position.hpp"
#include "types.hpp"


namespace Chess {

class Engine {

public:
    Engine() = default;

    void loadFen(std::string);
    std::string generateFen();

    const Piece* getBoard();

private:
    Position position;
};

}