#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <map>

class Indicator
{
public:
	Indicator();
	Indicator(std::vector<std::string>,float radius = 2,sf::Color color = sf::Color::Red);
	
	void draw(sf::RenderWindow&);
	bool isEmpty() const { return ind.empty(); };
	std::map<std::string, sf::CircleShape*> getPos();
	~Indicator();

private:
	std::map<std::string,sf::CircleShape*> ind;
};

