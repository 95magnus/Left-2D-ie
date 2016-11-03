#include "StateSettings.h"

StateSettings::StateSettings(Game* game) : StateBase(game) {

}

StateSettings::~StateSettings() {

}

void StateSettings::update(float deltaTime) {

}

void StateSettings::draw() {
    sf::Text title("Left[2D]ie", game->getFont(), 100);
    title.setColor(sf::Color::Red);
    title.setPosition(200, 50);

    sf::Text text("Settings state", game->getFont());
    text.setColor(sf::Color::Red);
    text.setPosition(300, 300);

    game->getWindow().draw(text);
    game->getWindow().draw(title);
}