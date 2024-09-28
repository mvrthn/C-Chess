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

    sf::Font font;
    font.loadFromFile("../res/font/Poppins-Medium.ttf");

    int size = 16;
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(size);

    float p = boardSize - size - 4;
    for(int i = 0; i < 8; i++) {
        text.setFillColor(i % 2 ? black : white);
        text.setString(char('a' + i));
        text.setPosition({i * n + 4, p});
        renderTexture.draw(text);
        text.setString(char('8' - i));
        text.setPosition({boardSize - size, i * n + 4});
        renderTexture.draw(text);
    }

    renderTexture.display();

    texture = sf::Texture(renderTexture.getTexture());
}

void Board::draw(sf::RenderWindow& window) {
    window.draw(sf::Sprite(texture));
}


}