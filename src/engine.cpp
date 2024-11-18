#include "engine.hpp"


#include "utilities.hpp"


namespace Chess {

Engine::Engine() {
    BBTable::init();
}

void Engine::loadFen(std::string fen) {
    position.parseFen(fen);
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
    MoveList moveList(position);
    if(!moveList.contains(move)) return false;
    position.makeMove(move);
    return true;
}

}