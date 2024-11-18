#include "pieceSet.hpp"

#include "position.hpp"


namespace Chess {

PieceSet::PieceSet() {
    squareSize = -1;

    std::string path = "../../res/pieces/";
    std::string color[2] = {"white-", "black-"};
    std::string pieces[6] = {"pawn", "knight", "bishop", "rook", "queen", "king"};
    std::string ext = ".png";

    for(int i = 0; i < 12; i++) {
        pieceTextures[i].loadFromFile(path + color[i < 6 ? 0 : 1] + pieces[i % 6] + ext);
        sprites[i].setTexture(pieceTextures[i], true);
    }
}

void PieceSet::render(float size, const Position& position) {

    float sqSize = size / 8;
    if(sqSize != squareSize) rescale(sqSize);

    renderTexture.create(size, size);
    renderTexture.clear(sf::Color::Transparent);

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            Piece p;
            if((p = position.pieceOn((7 - i) * 8 + j)) == NO_PIECE) continue;
            int idx = Position::pieceIndex(p);
            sprites[idx].setPosition({j * squareSize, i * squareSize});
            renderTexture.draw(sprites[idx]);
        }
    }

    renderTexture.display();

    texture = renderTexture.getTexture();
} 

void PieceSet::draw(sf::RenderWindow& window) {
    window.draw(sf::Sprite(texture));
}

void PieceSet::rescale(float size) {
    squareSize = size;
    float scale = size / pieceSize;

    for(int i = 0; i < 12; i++) {
        sprites[i].setScale({scale, scale});
    }
}

}