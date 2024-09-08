#pragma once


#include <SFML/Graphics.hpp>

#include "types.hpp"
#include "position.hpp"


namespace Chess {

class PieceSet {

#define pieceSize 128

public:
    PieceSet();

    void render(float, const Position&);

    void draw(sf::RenderWindow&);

private:
    void rescale(float);

    sf::RenderTexture renderTexture;
    sf::Texture texture;
    sf::Texture pieceTextures[12];
    sf::Sprite sprites[12];
    float squareSize;
};

}