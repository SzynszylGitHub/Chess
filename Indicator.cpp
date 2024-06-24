#include "Indicator.h"


std::string ToChessNotationi(const sf::Vector2f position) {

    int column = int(std::floor(position.x / 100)) + 1;
    int row = int(std::floor(position.y / 100)) + 1;

    char chessColumn = 'A' + column - 1;
    char chessRow = '1' + row - 1;

    std::string chessNotation;
    chessNotation += chessColumn;
    chessNotation += chessRow;

    return chessNotation;
}
sf::Vector2f ToPositioni(const std::string& chessNotation) {
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

Indicator::Indicator() {}



Indicator::Indicator(std::vector<std::string> pos,float radius,sf::Color color) {
	for (auto& el : pos) {
        ind[el] = new sf::CircleShape(radius);
        auto pozycja = ToPositioni(el);
        pozycja = sf::Vector2f(pozycja.x + (50 - radius), pozycja.y + (50 - radius));
        ind[el]->setPosition(pozycja);
        ind[el]->setFillColor(color);
	}
}
void Indicator::draw(sf::RenderWindow& handle) {
    for (const auto& n : ind)
        handle.draw(*n.second);
    
}

std::map<std::string, sf::CircleShape*> Indicator::getPos() {
    return ind;
}

Indicator::~Indicator() {
    for (auto& n : ind) 
        if(n.second != nullptr)
            delete n.second;
    
}
