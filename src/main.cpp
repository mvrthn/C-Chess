#include <iostream>

#include "position.hpp"


int main() {
    Chess::Position p;
    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"; 
    p.parseFen(fen);
    std::cout << p;
    return 0;
}