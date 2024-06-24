#pragma once
#include "Piece.h"
#include "Indicator.h"
#include "PromotionMenu.h"
#include <cmath>
#include <cctype>
#include <string>

void right_click(const sf::RenderWindow&, const sf::Event&, Board&);
sf::Vector2f getMousePosition(const sf::RenderWindow&);

bool click_sth(sf::Event&, sf::Keyboard::Key);

void handlePawnPromotion(Board& board, sf::RenderWindow& window, sf::Font& font, sf::Texture& queenTexture, sf::Texture& rookTexture, sf::Texture& bishopTexture, sf::Texture& knightTexture);
bool pick_piece(const sf::RenderWindow&, sf::Event&, Board&);
void setBoardToPlay(Board& board);
std::pair<std::vector<std::string>,Figure*> posible_move(const sf::RenderWindow& window, sf::Event& event, Board& table);
bool pick_indicator(const sf::RenderWindow&, const sf::Event&, Board&,std::vector<std::string>&, Figure*);