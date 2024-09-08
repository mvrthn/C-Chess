#pragma once


#include <SFML/Graphics.hpp>

#include "types.hpp"


namespace Chess {

class Board {

public:
    void render(float);
    void draw(sf::RenderWindow&);

private:
    sf::RenderTexture renderTexture;
    sf::Texture texture;

    sf::Color white = sf::Color(238, 232, 170);
    sf::Color black = sf::Color(139, 69, 19);
};

}