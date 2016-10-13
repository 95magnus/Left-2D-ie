#include "StateMainMenu.h"

StateMainMenu::StateMainMenu(Game* game) : StateBase(game) {

}

StateMainMenu::~StateMainMenu() {

}

void StateMainMenu::update() {

}

void StateMainMenu::draw() {
    sf::Text title("Left[2D]ie", game->getFont(), 100);
    title.setColor(sf::Color::Red);
    title.setPosition(200, 50);

    sf::Text text("Main menu state", game->getFont());
    text.setColor(sf::Color::Red);
    text.setPosition(300, 300);

    game->getWindow().draw(text);
    game->getWindow().draw(title);
}
