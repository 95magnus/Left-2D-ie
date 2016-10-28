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

    game->getWindow().draw(title);
    game->(Button(30,30,"Play"));

}

