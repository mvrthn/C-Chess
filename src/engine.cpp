#include "engine.hpp"


#include "utilities.hpp"


namespace Chess {

Engine::Engine() {
    BBTable::init();
}

void Engine::loadFen(std::string fen) {
    position.parseFen(fen);
    moveList.update(position);
}

std::string Engine::generateFen() const {
    return position.fen();
}

const Position& Engine::getPosition() const {
    return position;
}

Color Engine::colorOnMove() const {
    return position.getColorOnMove();
}

bool Engine::step(Move move) {
    if(!moveList.contains(move)) return false;
    position.makeMove(move);
    moveList.update(position);
    return true;
}

}