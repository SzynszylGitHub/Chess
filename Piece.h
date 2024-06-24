#pragma once
#include "Figure.h"

struct Rook : public Figure {
    Rook(const std::string& path = "asset/Piece/Rook_white.png"
        , const std::string& name = "Rook"
        , const sf::Color& color = sf::Color::White)
        : Figure(path, name) {
        setColor(color);
    }
    std::vector<std::string> findMove(Board&) override;
};

struct Knight : public Figure {
    Knight(const std::string& path = "asset/Piece/Knight_white.png"
        , const std::string& name = "Knight"
        , const sf::Color& color = sf::Color::White)
        : Figure(path, name) {
        setColor(color);
    }
    char getName() override;
    std::vector<std::string> findMove(Board&) override;
};

struct Bishop : public Figure {
    Bishop(const std::string& path = "asset/Piece/Bishop_white.png"
        , const std::string& name = "Bishop"
        , const sf::Color& color = sf::Color::White)
        : Figure(path, name) {
        setColor(color);
    }
    std::vector<std::string> findMove(Board&) override;
};

struct King : public Figure {
    King(const std::string& path = "asset/Piece/King_white.png"
        , const std::string& name = "King"
        , const sf::Color& color = sf::Color::White)
        : Figure(path, name) {
        setColor(color);
    }
    std::vector<std::string> findMove(Board&) override;
};

struct Queen : public Figure {
    Queen(const std::string& path = "asset/Piece/Queen_white.png"
        , const std::string& name = "Queen"
        , const sf::Color& color = sf::Color::White)
        : Figure(path, name) {
        setColor(color);
    }
    std::vector<std::string> findMove(Board&) override;
};

struct Pawn : public Figure {
    Pawn(const std::string& path = "asset/Piece/Pawn_white.png"
        , const std::string& name = "Pawn"
        , const sf::Color& color = sf::Color::White)
        : Figure(path, name) {
        setColor(color);
    }
    bool canPromote();
    std::vector<std::string> findMove(Board&) override;
};

