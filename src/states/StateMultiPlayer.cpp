#include "StateMultiPlayer.h"

StateMultiPlayer::StateMultiPlayer(Game* game) : StateBase(game) {

}

StateMultiPlayer::~StateMultiPlayer() {

}

void StateMultiPlayer::update(float deltaTime) {

}

void StateMultiPlayer::draw() {
    sf::Text title("Left[2D]ie", game->getFont(), 140);
    title.setColor(sf::Color::Red);
    title.setPosition(275, 50);

    sf::Text text("Multi player state", game->getFont());
    text.setColor(sf::Color::Red);
    text.setPosition(300, 300);

    game->getWindow().draw(text);
    game->getWindow().draw(title);


}
