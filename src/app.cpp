#include "app.hpp"

#include <SFML/Graphics.hpp>

#include "board.hpp"


namespace Chess {

#define defaultW 800
#define defaultH 600

void App::run() {
    
    sf::RenderWindow window(sf::VideoMode(defaultW, defaultH), "Chess");

    Board board;
    board.render(defaultH);
    
    sf::Sprite sprite(board.getTexture());

    while(window.isOpen()) {

        sf::Event event;
        while(window.pollEvent(event)) {

            if(event.type == sf::Event::Closed) {
                window.close();
            }

        }

        window.clear();

        window.draw(sprite);

        window.display();
    } 
}

}