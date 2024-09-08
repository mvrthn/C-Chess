#include "board.hpp"


namespace Chess {

void Board::render(float boardSize) {
    renderTexture.create(boardSize, boardSize);
    renderTexture.clear();

    float n = boardSize / 8;

    sf::RectangleShape squares[2] = {sf::RectangleShape({n, n}), sf::RectangleShape({n, n})};
    squares[0].setFillColor(white);
    squares[1].setFillColor(black);

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            int idx = (i + j) % 2;
            squares[idx].setPosition({i * n, j * n});
            renderTexture.draw(squares[idx]);
        }
    }

    renderTexture.display();

    texture = sf::Texture(renderTexture.getTexture());
}

void Board::draw(sf::RenderWindow& window) {
    window.draw(sf::Sprite(texture));
}


}