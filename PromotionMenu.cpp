#include "PromotionMenu.h"

PromotionMenu::PromotionMenu(sf::Font& font, sf::Texture& queenTexture, sf::Texture& rookTexture, sf::Texture& bishopTexture, sf::Texture& knightTexture) {
    background.setSize(sf::Vector2f(300, 100)); 
    background.setFillColor(sf::Color(0, 0, 0, 200));

    options[0].setTexture(queenTexture);
    options[1].setTexture(rookTexture);
    options[2].setTexture(bishopTexture);
    options[3].setTexture(knightTexture);

    for (int i = 0; i < 4; ++i) {
        options[i].setScale(1.0, 1.0);
        options[i].setPosition(10 + i * 70, 10);
    }

    isShown = false;
}

void PromotionMenu::show(sf::RenderWindow& window, sf::Vector2f position) {
    background.setPosition(position);
    isShown = true;

    while (isShown && window.isOpen()) {
        window.clear();
        window.draw(background);
        for (int i = 0; i < 4; ++i) {
            window.draw(options[i]);
        }
        window.display();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                for (int i = 0; i < 4; ++i) {
                    if (options[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        switch (i) {
                        case 0: selection = 'Q'; break;
                        case 1: selection = 'R'; break;
                        case 2: selection = 'B'; break;
                        case 3: selection = 'N'; break;
                        }
                        isShown = false;
                        break;
                    }
                }
            }
        }
    }
}

char PromotionMenu::getSelection(sf::RenderWindow& window) {
    return selection;
}