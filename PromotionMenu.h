#pragma once
#include "SFML/Graphics.hpp"
#include <string>

class PromotionMenu {
public:
    PromotionMenu(sf::Font& font, sf::Texture& queenTexture, sf::Texture& rookTexture, sf::Texture& bishopTexture, sf::Texture& knightTexture);
    void show(sf::RenderWindow& window, sf::Vector2f position);
    char getSelection(sf::RenderWindow& window);

private:
    sf::RectangleShape background;
    sf::Sprite options[4];
    char selection;
    bool isShown;
};
