#include "Piece.h"



bool isValidPosition(const sf::Vector2f& position) {
    // Check if the position is within the bounds of the chessboard (cell size  = 100 x 100)
    return position.x >= 0 && position.x < 800 && position.y >= 0 && position.y < 800;
}


std::vector<std::string> Rook::findMove(Board& table) {
    std::vector<std::string> possibleMoves;

    sf::Vector2f currentPosition = getPosition();
    std::string currentPosStr = ToChessNotation(currentPosition);

    // DEFINE THE POSSIBLE DIRECTIONS
    std::vector<sf::Vector2i> directions = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

    
    for (const auto& dir : directions) {
        sf::Vector2f nextPosition = currentPosition;
        while (true) {
            
            nextPosition += sf::Vector2f(dir.x * 100, dir.y * 100);
            
            std::string nextPosStr = ToChessNotation(nextPosition);
            
            
            if (!isValidPosition(nextPosition))
                break;
            
            
            if (table.isEmptyCell(nextPosStr)) {
                possibleMoves.push_back(nextPosStr);
            }
            else {
                
                if (table.isEnemy(nextPosStr, getColor())) {
                    possibleMoves.push_back(nextPosStr);
                }
                break;
            }
        }
    }

    return possibleMoves;
}

char Knight::getName() {
    return 'N';
}

std::vector<std::string> Knight::findMove(Board& table) {
    std::vector<std::string> possibleMoves;

    sf::Vector2f currentPosition = getPosition();
    std::string currentPosStr = ToChessNotation(currentPosition);

    // DEFINE THE POSSIBLE DIRECTIONS
    std::vector<sf::Vector2i> moves = {
        {1, 2}, {2, 1}, {2, -1}, {1, -2},
        {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}
    };

    
    for (const auto& move : moves) {
        
        sf::Vector2f nextPosition = currentPosition + sf::Vector2f(move.x * 100, move.y * 100);
        
        std::string nextPosStr = ToChessNotation(nextPosition);
        
        if (isValidPosition(nextPosition) && (table.isEmptyCell(nextPosStr) || table.isEnemy(nextPosStr, getColor()))) {
            possibleMoves.push_back(nextPosStr);
        }
    }

    return possibleMoves;
}

std::vector<std::string> Bishop::findMove(Board& table) {
    std::vector<std::string> possibleMoves;

    sf::Vector2f currentPosition = getPosition();
    std::string currentPosStr = ToChessNotation(currentPosition);

    // DEFINE THE POSSIBLE DIAGONALS
    std::vector<sf::Vector2i> directions = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

    
    for (const auto& dir : directions) {
        sf::Vector2f nextPosition = currentPosition;
        
        while (true) {
            
            nextPosition += sf::Vector2f(dir.x * 100, dir.y * 100);
            
            std::string nextPosStr = ToChessNotation(nextPosition);
            
            if (!isValidPosition(nextPosition))
                break;
            
            if (table.isEmptyCell(nextPosStr)) {
                possibleMoves.push_back(nextPosStr);
            }
            else {                
                if (table.isEnemy(nextPosStr, getColor())) {
                    possibleMoves.push_back(nextPosStr);
                }
                break;
            }
        }
    }

    return possibleMoves;
}

std::vector<std::string> King::findMove(Board& table) {
    std::vector<std::string> possibleMoves;

    sf::Vector2f currentPosition = getPosition();
    std::string currentPosStr = ToChessNotation(currentPosition);

    // DEFINE THE POSSIBLE MOVE
    std::vector<sf::Vector2i> directions = {
        {1, 0}, {1, 1}, {0, 1}, {-1, 1},
        {-1, 0}, {-1, -1}, {0, -1}, {1, -1}
    };

    for (const auto& dir : directions) {
        //next position
        sf::Vector2f nextPosition = currentPosition + sf::Vector2f(dir.x * 100, dir.y * 100);
        
        
        std::string nextPosStr = ToChessNotation(nextPosition);
        
        if (isValidPosition(nextPosition) && (table.isEmptyCell(nextPosStr) || table.isEnemy(nextPosStr, getColor()))) {
            possibleMoves.push_back(nextPosStr);
        }
    }

    return possibleMoves;
}

std::vector<std::string> Queen::findMove(Board& table) {
    std::vector<std::string> possibleMoves;

    sf::Vector2f currentPosition = getPosition();
    std::string currentPosStr = ToChessNotation(currentPosition);

    // DEFINE THE POSSIBLE DIRECTIONS 
    std::vector<sf::Vector2i> directions = {
        {1, 0}, {0, 1}, {-1, 0}, {0, -1},   // horizontal and vertical
        {1, 1}, {-1, 1}, {-1, -1}, {1, -1}  // diagonal
    };

    for (const auto& dir : directions) {
        sf::Vector2f nextPosition = currentPosition;
       
        while (true) {
            
            nextPosition += sf::Vector2f(dir.x * 100, dir.y * 100);
            
            std::string nextPosStr = ToChessNotation(nextPosition);
            
            if (!isValidPosition(nextPosition))
                break;
            
            if (table.isEmptyCell(nextPosStr)) {
                possibleMoves.push_back(nextPosStr);
            }
            else {
                
                if (table.isEnemy(nextPosStr, getColor())) {
                    possibleMoves.push_back(nextPosStr);
                }
                break;
            }
        }
    }

    return possibleMoves;
}


std::vector<std::string> Pawn::findMove(Board& table) {
    std::vector<std::string> possibleMoves;

    sf::Vector2f currentPosition = getPosition();
    std::string currentPosStr = ToChessNotation(currentPosition);

    int direction = (getColor() == sf::Color::White) ? 1 : -1;

    bool inStartingPosition = (currentPosStr[1] == '2' && direction == 1) 
        || (currentPosStr[1] == '7' && direction == -1);

    sf::Vector2f forwardCell(currentPosition.x, currentPosition.y + direction * 100);
    std::string forwardCellStr = ToChessNotation(forwardCell);

    // check if the pawn can move forward
    if (table.isEmptyCell(forwardCellStr)) {
        possibleMoves.push_back(forwardCellStr);

        if (inStartingPosition) {
            sf::Vector2f Square(currentPosition.x, currentPosition.y + 2 * direction * 100);
            std::string SquareStr = ToChessNotation(Square);
            if (table.isEmptyCell(SquareStr)) {
                possibleMoves.push_back(SquareStr);
            }
        }
    }

    // Check if the pawn can capture diagonally
    sf::Vector2f diagonalLeftSquare(currentPosition.x - 100, currentPosition.y + direction * 100);
    std::string diagonalLeftSquareStr = ToChessNotation(diagonalLeftSquare);
    if (table.isEnemy(diagonalLeftSquareStr, getColor())) {
        possibleMoves.push_back(diagonalLeftSquareStr);
    }

    sf::Vector2f diagonalRightSquare(currentPosition.x + 100, currentPosition.y + direction * 100);
    std::string diagonalRightSquareStr = ToChessNotation(diagonalRightSquare);
    if (table.isEnemy(diagonalRightSquareStr, getColor())) {
        possibleMoves.push_back(diagonalRightSquareStr);
    }
    
    // Check for en passant capture
    if ((currentPosStr[1] == '5' && direction == 1) || (currentPosStr[1] == '4' && direction == -1)) {
        std::string leftPosStr = ToChessNotation(sf::Vector2f(currentPosition.x - 100, currentPosition.y));
        std::string rightPosStr = ToChessNotation(sf::Vector2f(currentPosition.x + 100, currentPosition.y));

        if (table.canEnPassant(leftPosStr, getColor())) {
            possibleMoves.push_back(ToChessNotation(sf::Vector2f(currentPosition.x - 100, currentPosition.y + direction * 100)));
        }

        if (table.canEnPassant(rightPosStr, getColor())) {
            possibleMoves.push_back(ToChessNotation(sf::Vector2f(currentPosition.x + 100, currentPosition.y + direction * 100)));
        }
    }

    return possibleMoves;
}

bool Pawn::canPromote() {
    sf::Vector2f position = getPosition();
    std::string posStr = ToChessNotation(position);
    
    if ((getColor() == sf::Color::White && posStr[1] == '8') ||
        (getColor() == sf::Color::Black && posStr[1] == '1')) {
        return true;
    }
    return false;
}

