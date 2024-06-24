#include "Board.h"
#include "Piece.h"

Board::Board() : currentTurn(sf::Color::White) {}

void Board::initialize(float x, float y,sf::Color F1,sf::Color F2) {
    Cell square;
    chessboard.resize(size * size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            square.setPosition(x + i * 100,y + j * 100);
            if ((i + j) % 2 == 0) square.setColor(F1);
            else square.setColor(F2);

            chessboard.emplace_back(square);
        }
    }
    currentTurn = sf::Color::White;
}

void Board::switchTurn() {
    currentTurn = (currentTurn == sf::Color::White) ? sf::Color::Black : sf::Color::White;
}

sf::Color Board::getCurrentTurn() const {
    return currentTurn;
}


void Board::recordLastMove(const std::string& from, const std::string& to) {
    lastMove = { from, to };
}

bool Board::canEnPassant(const std::string& position, sf::Color color) {
    if (lastMove.second.empty()) return false;

    // The last move must be a two-square pawn move
    int direction = (color == sf::Color::White) ? -1 : 1;
    std::string expectedFrom = lastMove.second[0] + std::to_string(lastMove.second[1] - direction * 2);
    std::string expectedTo = lastMove.second;

    return (expectedFrom == lastMove.first && expectedTo == lastMove.second && lastMove.second == position);
}

void Board::drawBoard(sf::RenderWindow& handle) {
    handle.clear();
    // drawing clear board 
    for (auto& n : chessboard)
        n.draw(handle);

}

void Board::drawPiece(sf::RenderWindow& handle) {
    
    // drawing piece
    for (auto& n : Piece)
        n.second->draw(handle);

}

bool Board::isEmptyCell(std::string chessnotation) {
    auto it = Piece.find(chessnotation);
    if (it == Piece.end()) 
        return true;
    
    return false;
}

bool Board::isEnemy(const std::string& chessNotation, sf::Color color){
    auto it = Piece.find(chessNotation);
    if (it == Piece.end() || it->second == nullptr) {
        return false;
    }
    else {
        return (it->second->getColor() != color);
    }
}

bool Board::move(std::string start, std::string end) {
    return false;
}

void Board::print() {
    for (auto& n : Piece) {
        std::cout << n.first << "\n";
    }
}

void Board::markCell(sf::Vector2f mouse, sf::Color color) {

    for (auto& select : chessboard){
        if (select.isSelected(mouse)) {
            if (select.getColor() != color) {
                select.setColorC(color);
                return;
            }
            else {
                select.reset();
                return;
            }
        }
    }
}
void Board::resetMarker() {
    for (auto& select : chessboard)
        select.reset();
}

sf::Color Board::Win() {
    bool fWhite = false;
    bool fBlack = false;
    for (auto& n : Piece) {
        if (n.second == nullptr)
            continue;
        if (n.second->getName() == 'K' && n.second->getColor() == sf::Color::White) 
            fWhite = true;
        if (n.second->getName() == 'K' && n.second->getColor() == sf::Color::Black)
            fBlack = true;
    }

    if (!fWhite) return sf::Color::Black;
    if (!fBlack) return sf::Color::White;

    return sf::Color::Blue;
}

void Board::promotePawn(const std::string& position, char newPieceType) {
    auto it = Piece.find(position);
    if (it != Piece.end() && it->second != nullptr) {
        Figure* oldPawn = it->second;
        Figure* newPiece = nullptr;

        switch (newPieceType) {
        case 'Q':
            newPiece = new Queen("asset/Piece/Queen_" + std::string(oldPawn->getColor() == sf::Color::White ? "white.png" : "black.png"),
                "Queen", oldPawn->getColor());
            break;
        case 'R':
            newPiece = new Rook("asset/Piece/Rook_" + std::string(oldPawn->getColor() == sf::Color::White ? "white.png" : "black.png"),
                "Rook", oldPawn->getColor());
            break;
        case 'B':
            newPiece = new Bishop("asset/Piece/Bishop_" + std::string(oldPawn->getColor() == sf::Color::White ? "white.png" : "black.png"),
                "Bishop", oldPawn->getColor());
            break;
        case 'N':
            newPiece = new Knight("asset/Piece/Knight_" + std::string(oldPawn->getColor() == sf::Color::White ? "white.png" : "black.png"),
                "Knight", oldPawn->getColor());
            break;
        default:
            break; // Invalid input, no promotion
        }

        if (newPiece != nullptr) {
            newPiece->setPosition(ToPosition(position));
            Piece[position] = newPiece;
            delete oldPawn;
        }
    }
}



Figure* Board::operator[](std::string n) {
    return Piece[n];
}

Board::~Board() {
    for (auto& n : Piece) {
        delete n.second;
    }
}
