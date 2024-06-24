#pragma once
#include <SFML/Graphics.hpp>
#include "board.h"
class Board;
class Figure
{
public:
	Figure(std::string path="asset/", std::string name = "", int width = 100, int height = 100);
	virtual char getName();
	
	void setPosition(float x, float y);
	void setPosition(sf::Vector2f);
	sf::Vector2f getPosition();

	void draw(sf::RenderWindow&);
	void setColor(sf::Color m_color);
	sf::Color getColor();
	void setTexture(std::string path);
	void setTexture(sf::Texture);
	virtual std::vector<std::string> findMove(Board&)=0;
	bool isSelected = false;

private:
	sf::Texture texture;
	sf::Sprite Sp;
	int width;
	int height;
	sf::Color color = sf::Color::White;
	std::string name;
};

std::string ToChessNotation(const sf::Vector2f);
sf::Vector2f ToPosition(const std::string&);
