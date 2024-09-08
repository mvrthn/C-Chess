#include "app.hpp"

#include <SFML/Graphics.hpp>

#include "board.hpp"
#include "pieceSet.hpp"
#include "engine.hpp"


namespace Chess {

App::App() {
    engine.loadFen();

    board.render(defaultH);
    
    pieceSet.render(defaultH, engine.getPosition());
}

void App::run() {
    bool redraw = true;
    bool rerenderBoard = false;
    
    while(window.isOpen()) {

        sf::Event event;
        while(window.pollEvent(event)) {

            if(event.type == sf::Event::Closed) {
                window.close();
            }

        }

        if(rerenderBoard) {
            board.render(window.getSize().y);
            rerenderBoard = false;
        }

        if(redraw) {
            redraw = false;

            window.clear();

            board.draw(window);
            pieceSet.draw(window);

            window.display();
        }
    } 
}

}