#include "input_handling.h"
#include "Bar.h"

#define width 800
#define heigth 800

int main() {
    sf::Font font;
    font.loadFromFile("asset/Fonts/EnglishTowne.ttf");

    bool show_bar = true;
    Bar bar("Press Enter to start game", font);
    sf::Vector2f Bar_position(0, (heigth - bar.getRectangleSize().y) / 2);
    bar.setPosition(Bar_position);
    bar.setColorRectangle(sf::Color(0, 0, 0, 255 * 0.30));
    bar.reSizeCharacter(40);
    bar.setColorCharacter(sf::Color::White);
    bar.center();

    sf::Texture queenTexture, rookTexture, bishopTexture, knightTexture;
    queenTexture.loadFromFile("asset/Piece/Queen_white.png");
    rookTexture.loadFromFile("asset/Piece/Rook_white.png");
    bishopTexture.loadFromFile("asset/Piece/Bishop_white.png");
    knightTexture.loadFromFile("asset/Piece/Knight_white.png");

    sf::Keyboard::Key press;

    bool isOn = true;
    while (isOn) {
        Board board;
        board.initialize();
        bar.setString("Press Enter to start game");
        press = sf::Keyboard::Key::Enter;

        setBoardToPlay(board);
        sf::RenderWindow window(sf::VideoMode(width, heigth), "Hello");
        window.setFramerateLimit(60);

        sf::Event event;
        std::pair<std::vector<std::string>, Figure*> type;

        while (window.isOpen()) {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    isOn = false;
                }

                if (show_bar) {
                    if (click_sth(event, press)) {
                        show_bar = false;

                        if (press == sf::Keyboard::Key::R)
                            window.close();
                    }
                }

                if (!show_bar) {
                    right_click(window, event, board);
                    pick_indicator(window, event, board, type.first, type.second);
                    pick_piece(window, event, board);
                    type = posible_move(window, event, board);

                    // Handle pawn promotion after possible move
                    handlePawnPromotion(board, window, font, queenTexture, rookTexture, bishopTexture, knightTexture);
                }

                if (board.Win() != sf::Color::Blue) {
                    bar.setString("Click r to restart game.");
                    show_bar = true;
                    press = sf::Keyboard::Key::R;
                }
            }

            Indicator indicator(type.first, 10.f);

            window.clear();

            board.drawBoard(window);
            board.drawPiece(window);
            indicator.draw(window);

            if (show_bar)
                bar.draw(window);

            window.display();
        }
    }
    return 0;
}
