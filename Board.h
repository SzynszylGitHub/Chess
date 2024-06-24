#pragma once
#include "Cell.h"
#include <iostream>
#include <vector>
#include <map>
#include "Figure.h"


class Figure;
class Board
{
public:
	Board();
	void initialize(float x = 0, float y = 0,
		sf::Color F1 = sf::Color::White, sf::Color F2 = sf::Color::Green);
	void switchTurn();
	sf::Color getCurrentTurn() const;
	void print();
	bool isEmptyCell(std::string chessnotation);
	bool isEnemy(const std::string& chessNotation, sf::Color color);
	void drawBoard(sf::RenderWindow& handle);
	void drawPiece(sf::RenderWindow& handle);
	bool move(std::string,std::string);
	void markCell(sf::Vector2f,sf::Color = sf::Color::Yellow);
	void resetMarker();
	void promotePawn(const std::string& position, char newPieceType);
	bool canEnPassant(const std::string& position, sf::Color color);
	void recordLastMove(const std::string& from, const std::string& to);
	sf::Color Win();
	Figure* operator[](std::string);
	
	std::map<std::string, Figure*> Piece;
	~Board();
private:
	int size = 8;
	bool isSelected = true;
	
	sf::Color currentTurn; 
	std::pair<std::string, std::string> lastMove; 
	std::vector<Cell> chessboard;
	
	
};



