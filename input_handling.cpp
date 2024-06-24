#include "input_handling.h"

// Function to handle right-click events
void right_click(const sf::RenderWindow& window, const sf::Event& event, Board& board) {
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right) {
        sf::Vector2f mousePosition = getMousePosition(window);
        board.markCell(mousePosition);
    }
}

// Function to get mouse position in world coordinates
sf::Vector2f getMousePosition(const sf::RenderWindow& window) {
    return window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

bool click_sth(sf::Event& event, sf::Keyboard::Key code) {
    if (event.key.code == code) {
        return true;
    }
    return false;
}

bool corect(std::string newPos,std::vector<std::string> validation, bool f = true) {
     if (f) {
         std::cout << "Move: \n";
         for (auto& n : validation)
             std::cout << n <<" ";
         std::cout << std::endl;
     }
     
     for (auto& n : validation) {
         if (n == newPos) 
             return true;
     }
     return false;
}

std::pair<std::vector<std::string>, Figure*> posible_move(const sf::RenderWindow& window, sf::Event& event, Board& table) {
    static std::string primary = "";
    static Figure* figure = nullptr;
    static std::vector<std::string> move;

    sf::Vector2f mouse = getMousePosition(window);
    std::string chess = ToChessNotation(mouse);

    if (event.type == sf::Event::MouseButtonPressed
        && event.mouseButton.button == sf::Mouse::Left) {
        move.clear();
        try {
            figure = table.Piece.at(chess);
            primary = chess;

            // Check if the picked piece belongs to the current player
            if (figure->getColor() != table.getCurrentTurn()) {
                figure = nullptr;
                primary = "";
            }
        }
        catch (...) {
            figure = nullptr;
            primary = "";
        }
    }

    if (event.type == sf::Event::MouseButtonReleased
        && event.mouseButton.button == sf::Mouse::Left) {
        if (chess == primary && figure != nullptr) {
            move = figure->findMove(table);

            // Include en passant moves if it's a pawn
            if (figure->getName() == 'P') {
                std::vector<std::string> enPassantMoves = figure->findMove(table);
                move.insert(move.end(), enPassantMoves.begin(), enPassantMoves.end());
            }
        }
    }
    return std::make_pair(move, figure);
}

bool pick_indicator(const sf::RenderWindow& handle, const sf::Event& event,
    Board& table, std::vector<std::string>& move, Figure* figure) {

    sf::Vector2f mouse = getMousePosition(handle);
    std::string chess = ToChessNotation(mouse);

    if (event.type == sf::Event::MouseButtonPressed
        && event.mouseButton.button == sf::Mouse::Left) {
        for (auto& n : move) {
            if (n == chess) {
                // Handle en passant capture
                if (figure->getName() == 'P' && chess[0] != ToChessNotation(figure->getPosition())[0] && table.isEmptyCell(chess)) {
                    std::string capturePos ="" + chess[0] + ToChessNotation(figure->getPosition())[1];
                    delete table.Piece[capturePos];
                    table.Piece.erase(capturePos);
                }

                table.Piece.erase(ToChessNotation(figure->getPosition()));
                table.Piece[chess] = figure;
                figure->setPosition(ToPosition(chess));

                table.recordLastMove(ToChessNotation(figure->getPosition()), chess);

                table.switchTurn();

                table.resetMarker();
                return true;
            }
        }
    }

    return false;
}

bool pick_piece(const sf::RenderWindow& window, sf::Event& event, Board& table) {
    static bool up = false;
    static Figure* figure = nullptr;
    static std::string primary;
    static std::vector<std::string> validation_move;

    sf::Vector2f mouse = getMousePosition(window);
    std::string chess = ToChessNotation(mouse);

    if (event.type == sf::Event::MouseButtonPressed
        && event.mouseButton.button == sf::Mouse::Left
        && !up) {
        try {
            figure = table.Piece.at(chess);
        }
        catch (...) {
            return false;
            up = false;
        }

        // Check if the picked piece belongs to the current player
        if (figure->getColor() != table.getCurrentTurn()) {
            figure = nullptr;
            return false;
        }

        validation_move = figure->findMove(table);
        primary = chess;
        figure = table[chess];
        up = true;
    }

    if (up && figure != nullptr) {
        sf::Vector2f litle(mouse.x - 50, mouse.y - 50);
        figure->setPosition(litle);
    }

    if (event.type == sf::Event::MouseButtonReleased
        && event.mouseButton.button == sf::Mouse::Left
        && up) {
        if (!corect(chess, validation_move, false)) {
            figure->setPosition(ToPosition(primary));
            figure = nullptr;
            primary = "";
            up = false;
            table.resetMarker();
            validation_move.clear();
            return false;
        }

        // Handle en passant capture
        if (figure->getName() == 'P' && chess[0] != primary[0] && table.isEmptyCell(chess)) {
            std::string capturePos = chess[0] + primary[1]+"";
            delete table.Piece[capturePos];
            table.Piece.erase(capturePos);
        }

        figure->setPosition(ToPosition(chess));
        table.Piece.erase(primary);
        table.Piece[chess] = figure;

        // Record the move
        table.recordLastMove(primary, chess);

        // Switch the turn after a valid move
        table.switchTurn();

        table.resetMarker();
        figure = nullptr;
        primary = "";
        up = false;
        validation_move.clear();
    }

    return false;
}


void setBoardToPlay(Board& board) {
    // Clear the board first
    board.Piece.clear();

    // Place white pieces
    
    board.Piece["A1"] = new Rook;
    board.Piece["A1"]->setPosition(ToPosition("A1"));
    board.Piece["B1"] = new Knight;
    board.Piece["B1"]->setPosition(ToPosition("B1"));
    board.Piece["C1"] = new Bishop;
    board.Piece["C1"]->setPosition(ToPosition("C1"));
    board.Piece["D1"] = new Queen;
    board.Piece["D1"]->setPosition(ToPosition("D1"));
    board.Piece["E1"] = new King;
    board.Piece["E1"]->setPosition(ToPosition("E1"));
    board.Piece["F1"] = new Bishop;
    board.Piece["F1"]->setPosition(ToPosition("F1"));
    board.Piece["G1"] = new Knight;
    board.Piece["G1"]->setPosition(ToPosition("G1"));
    board.Piece["H1"] = new Rook;
    board.Piece["H1"]->setPosition(ToPosition("H1"));


    board.Piece["A2"] = new Pawn;
    board.Piece["A2"]->setPosition(ToPosition("A2"));
    
    board.Piece["B2"] = new Pawn;
    board.Piece["B2"]->setPosition(ToPosition("B2"));
    
    board.Piece["C2"] = new Pawn;
    board.Piece["C2"]->setPosition(ToPosition("C2"));

    board.Piece["D2"] = new Pawn;
    board.Piece["D2"]->setPosition(ToPosition("D2"));

    board.Piece["E2"] = new Pawn;
    board.Piece["E2"]->setPosition(ToPosition("E2"));

    board.Piece["F2"] = new Pawn;
    board.Piece["F2"]->setPosition(ToPosition("F2"));

    board.Piece["G2"] = new Pawn;
    board.Piece["G2"]->setPosition(ToPosition("G2"));

    board.Piece["H2"] = new Pawn;
    board.Piece["H2"]->setPosition(ToPosition("H2"));

    // place black piece
    board.Piece["A8"] = new Rook("asset/Piece/Rook_black.png","Rook",sf::Color::Black);
    board.Piece["A8"]->setPosition(ToPosition("A8"));
    board.Piece["B8"] = new Knight("asset/Piece/Knight_black.png", "Knight", sf::Color::Black);
    board.Piece["B8"]->setPosition(ToPosition("B8"));
    board.Piece["C8"] = new Bishop("asset/Piece/Bishop_black.png", "Bishop", sf::Color::Black);
    board.Piece["C8"]->setPosition(ToPosition("C8"));
    board.Piece["D8"] = new Queen("asset/Piece/Queen_black.png", "Queen", sf::Color::Black);
    board.Piece["D8"]->setPosition(ToPosition("D8"));
    board.Piece["E8"] = new King("asset/Piece/King_black.png", "King", sf::Color::Black);
    board.Piece["E8"]->setPosition(ToPosition("E8"));
    board.Piece["F8"] = new Bishop("asset/Piece/Bishop_black.png", "Bishop", sf::Color::Black);
    board.Piece["F8"]->setPosition(ToPosition("F8"));
    board.Piece["G8"] = new Knight("asset/Piece/Knight_black.png", "Knight", sf::Color::Black);
    board.Piece["G8"]->setPosition(ToPosition("G8"));
    board.Piece["H8"] = new Rook("asset/Piece/Rook_black.png", "Rook", sf::Color::Black);
    board.Piece["H8"]->setPosition(ToPosition("H8"));


    board.Piece["A7"] = new Pawn("asset/Piece/Pawn_black.png", "Pawn", sf::Color::Black);
    board.Piece["A7"]->setPosition(ToPosition("A7"));

    board.Piece["B7"] = new Pawn("asset/Piece/Pawn_black.png", "Pawn", sf::Color::Black);
    board.Piece["B7"]->setPosition(ToPosition("B7"));

    board.Piece["C7"] = new Pawn("asset/Piece/Pawn_black.png", "Pawn", sf::Color::Black);
    board.Piece["C7"]->setPosition(ToPosition("C7"));

    board.Piece["D7"] = new Pawn("asset/Piece/Pawn_black.png", "Pawn", sf::Color::Black);
    board.Piece["D7"]->setPosition(ToPosition("D7"));

    board.Piece["E7"] = new Pawn("asset/Piece/Pawn_black.png", "Pawn", sf::Color::Black);
    board.Piece["E7"]->setPosition(ToPosition("E7"));

    board.Piece["F7"] = new Pawn("asset/Piece/Pawn_black.png", "Pawn", sf::Color::Black);
    board.Piece["F7"]->setPosition(ToPosition("F7"));

    board.Piece["G7"] = new Pawn("asset/Piece/Pawn_black.png", "Pawn", sf::Color::Black);
    board.Piece["G7"]->setPosition(ToPosition("G7"));

    board.Piece["H7"] = new Pawn("asset/Piece/Pawn_black.png", "Pawn", sf::Color::Black);
    board.Piece["H7"]->setPosition(ToPosition("H7"));
}


void handlePawnPromotion(Board& board, sf::RenderWindow& window, sf::Font& font, sf::Texture& queenTexture, sf::Texture& rookTexture, sf::Texture& bishopTexture, sf::Texture& knightTexture) {
    PromotionMenu promotionMenu(font, queenTexture, rookTexture, bishopTexture, knightTexture);

    for (auto& [position, piece] : board.Piece) {
        if (piece != nullptr && piece->getName() == 'P') {
            Pawn* pawn = dynamic_cast<Pawn*>(piece);
            if (pawn != nullptr && pawn->canPromote()) {
                promotionMenu.show(window, pawn->getPosition());
                char newPieceType = promotionMenu.getSelection(window);

                if (newPieceType != '\0') {
                    board.promotePawn(position, newPieceType);
                }
            }
        }
    }
}