#pragma once


#include <SFML/Graphics.hpp>

#include "board.hpp"
#include "pieceSet.hpp"
#include "engine.hpp"


namespace Chess {

class App {

#define defaultW 712
#define defaultH 512

public:
    App();

    void run();

private:
    sf::RenderWindow window = sf::RenderWindow({defaultW, defaultH}, "Chess", sf::Style::Close);
    Engine engine;
    Board board;
    PieceSet pieceSet;
};

}