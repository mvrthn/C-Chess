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
    void mousePressed(sf::Event&);
    void mouseReleased(sf::Event&);

    bool cursorOnBoard(sf::Event&);
    Square readSquare(int, int);

    void callEngine();

private:
    sf::RenderWindow window = sf::RenderWindow({defaultW, defaultH}, "Chess", sf::Style::Close);
    Engine engine;
    Board board;
    PieceSet pieceSet;
    MoveTry move;
    RenderCond render;
    int boardSize;
    int squareSize;
};

}