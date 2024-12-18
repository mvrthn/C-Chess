#include "app.hpp"

#include <SFML/Graphics.hpp>

#include "board.hpp"
#include "pieceSet.hpp"
#include "engine.hpp"
#include "types.hpp"
#include "utilities.hpp"


namespace Chess {

App::App() {
    boardSize = defaultH;
    squareSize = boardSize / 8;
    render = DRAW;

    engine.loadFen();

    board.render(boardSize);
    
    pieceSet.render(boardSize, engine.getPosition());
}

void App::run() {
    while(window.isOpen()) {

        sf::Event event;
        while(window.pollEvent(event)) {

            if(event.type == sf::Event::Closed) {
                window.close();
            }

            else if(event.type == sf::Event::MouseButtonPressed) {
                mousePressed(event);
            }
            else if(event.type == sf::Event::MouseButtonReleased) {
                mouseReleased(event);
            }

        }

        window.clear();

        board.draw(window);
        pieceSet.draw(window);

        window.display();

        // if(render & RENDER_BOARD) {
        //     render ^= RENDER_BOARD;
        //     board.render(boardSize);
        // }
        // if(render & RENDER_PIECE_SET) {
        //     render ^= RENDER_PIECE_SET;
        //     pieceSet.render(boardSize, engine.getPosition());
        // }

        // if(render & DRAW) {
        //     render ^= DRAW;

        //     window.clear();

        //     board.draw(window);
        //     pieceSet.draw(window);

        //     window.display();
        // }
    } 
}

void App::mousePressed(sf::Event& event) {
    if(!cursorOnBoard(event)) return;
    if(event.mouseButton.button == sf::Mouse::Button::Left) {
        Square sq = readSquare(event.mouseButton.x, event.mouseButton.y);
        if(move.from == SQ_NONE) {
            move.from = sq;
        }
        else {
            move.to = sq;
        }
    }
    else if(event.mouseButton.button == sf::Mouse::Button::Right) {

    }
}

void App::mouseReleased(sf::Event& event) {
    if(!cursorOnBoard(event)) return;
    if(event.mouseButton.button == sf::Mouse::Button::Left) {
        Square sq = readSquare(event.mouseButton.x, event.mouseButton.y);
        if(move.to == SQ_NONE) {
            if(move.from != sq) {
                move.to = sq;
                callEngine();
            }
        }
        else if(move.to == sq) {
            callEngine();
        }
        else {
            move.clear();
        }
    }
    else if(event.mouseButton.button == sf::Mouse::Button::Right) {

    }
}

bool App::cursorOnBoard(sf::Event& event) {
    if(event.mouseButton.x > boardSize) return false;
    if(event.mouseButton.y > boardSize) return false;
    return true;
}

Square App::readSquare(int x, int y) {
    return Square((x / squareSize) + 8 * (7 - (y / squareSize)));
}

void App::callEngine() {
    Move m(move.from, move.to);
    move.clear();
    if(!engine.step(m)) return;
    pieceSet.render(boardSize, engine.getPosition());
    // render &= RENDER_PIECE_SET;
    // render &= DRAW;
}

}