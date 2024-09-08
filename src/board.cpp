#include "board.hpp"


namespace Chess {

void Board::render(float boardSize) {
    texture.create(boardSize, boardSize);
    texture.clear();

    float n = boardSize / 8;

    sf::RectangleShape squares[2] = {sf::RectangleShape({n, n}), sf::RectangleShape({n, n})};
    squares[0].setFillColor(white);
    squares[1].setFillColor(black);

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            int idx = (i + j) % 2;
            squares[idx].setPosition({i * n, j * n});
            texture.draw(squares[idx]);
        }
    }

    texture.display();
}

const sf::Texture Board::getTexture() {
    return texture.getTexture();
}

}