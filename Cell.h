#pragma once
#include <SFML/Graphics.hpp>

class Cell {
public:
    
    Cell(float size= 100, sf::Color color = sf::Color::Yellow);
    void setPosition(float x, float y);
    void draw(sf::RenderWindow&);
    sf::Vector2f getPosition();
    bool isSelected(const sf::Vector2f);
    void setColor(sf::Color);
    void setColorC(sf::Color);
    void reset();
    sf::Color getColor();

private:
    float m_size;
    sf::Color m_color;
    sf::Color s_color;
    sf::RectangleShape m_square;
};
