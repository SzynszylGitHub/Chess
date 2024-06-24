#include "Figure.h"

Figure::Figure(std::string path,std::string name, int width, int height) :name(name),width(width), height(height) {
	texture.loadFromFile(path);
	Sp.setTexture(texture); 
}
void Figure::draw(sf::RenderWindow& handle) {
	handle.draw(Sp);
}

char Figure::getName() {
	return name[0];
}
void Figure::setColor(sf::Color m_color) {
	color = m_color;
}
sf::Color Figure::getColor() {
	return color;
}
void Figure::setTexture(std::string path) {
	texture.loadFromFile(path);
	Sp.setTexture(texture);
}
void Figure::setTexture(sf::Texture texture) {
	this->texture = texture;
	Sp.setTexture(this->texture);
}

void Figure::setPosition(float x, float y) {
	Sp.setPosition(x, y);
}
void Figure::setPosition(sf::Vector2f position) {
	Sp.setPosition(position);
}

sf::Vector2f Figure::getPosition() {
	return Sp.getPosition();
}

std::string ToChessNotation(const sf::Vector2f position) {

    int column = int(std::floor(position.x / 100)) + 1;
    int row = int(std::floor(position.y / 100)) + 1;

    char chessColumn = 'A' + column - 1;
    char chessRow = '1' + row - 1;

    std::string chessNotation;
    chessNotation += chessColumn;
    chessNotation += chessRow;

    return chessNotation;
}

sf::Vector2f ToPosition(const std::string& chessNotation) {
    if (chessNotation.size() < 2) {
        return sf::Vector2f(-1, -1);
    }

    char chessColumn = std::toupper(chessNotation[0]);
    char chessRow = chessNotation[1];

    int column = chessColumn - 'A';
    int row = chessRow - '1';

    float cellSize = 100;

    sf::Vector2f position;
    position.x = column * cellSize;
    position.y = row * cellSize;

    return position;
}
