#include "engine.hpp"


#include "bitboard.hpp"
#include "moveGen.hpp"
#include "utilities.hpp"


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

void Engine::step() {
    MoveList moveList(position);
    
    for(auto move : moveList) {
        printMove(move.from(), move.to());
    }
}

}