#include "Cell.h"

Cell::Cell(float size, sf::Color color) : m_size(size), m_color(color) {
    m_square.setSize(sf::Vector2f(size, size));
    m_square.setFillColor(color);
}
void Cell::setPosition(float x, float y) {
    m_square.setPosition(x, y);
}
sf::Vector2f Cell::getPosition() {
    return m_square.getPosition();
}
void Cell::draw(sf::RenderWindow& window) {
    window.draw(m_square);
}
void Cell::setColor(sf::Color color) {
    m_color = color;
    s_color = m_color;
    m_square.setFillColor(m_color);
}
void Cell::setColorC(sf::Color color) {
    s_color = m_color;
    m_color = color;
    m_square.setFillColor(color);
}
bool Cell::isSelected(const sf::Vector2f mousePos) {
    return m_square.getGlobalBounds().contains(mousePos);
}
void Cell::reset() {
    m_color = s_color;
    m_square.setFillColor(m_color);
}
sf::Color Cell::getColor() {
    return m_color;
}