#pragma once


#include <SFML/Graphics.hpp>

#include "board.hpp"
#include "pieceSet.hpp"
#include "engine.hpp"


namespace Chess {

class App {

#define defaultW 840
#define defaultH 640

public:
    App();

    void run();

private:
    sf::RenderWindow window = sf::RenderWindow({defaultW, defaultH}, "Chess", sf::Style::Close);
    Engine engine;
    Board board;
    PieceSet pieceSet;
    Move move;
    int boardSize;
    int squareSize;

    void mousePressed(sf::Event&, RenderCond&);
    void mouseReleased(sf::Event&, RenderCond&);

    bool cursorOnBoard(sf::Event&);
    Square readSquare(int, int);
};

}