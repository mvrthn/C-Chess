#include "app.hpp"

#include <SFML/Graphics.hpp>

#include "board.hpp"
#include "pieceSet.hpp"
#include "engine.hpp"
#include "types.hpp"


namespace Chess {

App::App() {
    boardSize = defaultH;
    squareSize = boardSize / 8;

    engine.loadFen();

    board.render(boardSize);
    
    pieceSet.render(boardSize, engine.getPosition());
}

void App::run() {
    RenderCond render = NO_RENDER;
    
    while(window.isOpen()) {

        sf::Event event;
        while(window.pollEvent(event)) {

            if(event.type == sf::Event::Closed) {
                window.close();
            }

            else if(event.type == sf::Event::MouseButtonPressed) {
                mousePressed(event, render);
            }
            else if(event.type == sf::Event::MouseButtonReleased) {
                mouseReleased(event, render);
            }

        }

        if(render & RENDER_BOARD) {
            render ^= RENDER_BOARD;
            board.render(boardSize);
        }
        if(render & RENDER_PIECE_SET) {
            render ^= RENDER_PIECE_SET;
            pieceSet.render(boardSize, engine.getPosition());
        }

        if(render & DRAW) {
            render ^= DRAW;

            window.clear();

            board.draw(window);
            pieceSet.draw(window);

            window.display();
        }
    } 
}

void App::mousePressed(sf::Event& event, RenderCond& render) {
    if(!cursorOnBoard(event)) return;
    if(event.mouseButton.button == sf::Mouse::Button::Left) {
        
    }
    else if(event.mouseButton.button == sf::Mouse::Button::Right) {

    }
}

void App::mouseReleased(sf::Event& event, RenderCond& render) {
    if(!cursorOnBoard(event)) return;
    if(event.mouseButton.button == sf::Mouse::Button::Left) {
        
    }
    else if(event.mouseButton.button == sf::Mouse::Button::Right) {

    }
}

bool App::cursorOnBoard(sf::Event& event) {
    if(event.mouseButton.x > boardSize) return false;
    if(event.mouseButton.y > boardSize) return false;
    return true;
}

Square App::getSquare(int x, int y) {
    return x / boardSize
}

}