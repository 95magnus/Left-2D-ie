#include "StateMultiPlayer.h"

StateMultiPlayer::StateMultiPlayer(Game* game) : StateBase(game) {

}

StateMultiPlayer::~StateMultiPlayer() {

}

void StateMultiPlayer::update() {

}

void StateMultiPlayer::draw() {
    sf::Text title("Left[2D]ie", game->getFont(), 100);
    title.setFillColor(sf::Color::Red);
    title.setPosition(200, 50);

    sf::Text text("Multi player state", game->getFont());
    text.setFillColor(sf::Color::Red);
    text.setPosition(300, 300);

    game->getWindow().draw(text);
    game->getWindow().draw(title);
}