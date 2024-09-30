#include "engine.hpp"


#include "bitboard.hpp"


namespace Chess {

Engine::Engine() {
    BBTable::init();
}

void Engine::loadFen(std::string fen) {
    position.parseFen(fen);
}

std::string Engine::generateFen() {
    return position.fen();
}

const Position& Engine::getPosition() {
    return position;
}

}