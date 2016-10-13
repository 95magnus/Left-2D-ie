#include "StateHighScore.h"

StateHighScore::StateHighScore(Game* game) : StateBase(game) {

}

StateHighScore::~StateHighScore() {

}

void StateHighScore::update() {

}

void StateHighScore::draw() {
    sf::Text title("Left[2D]ie", game->getFont(), 100);
    title.setColor(sf::Color::Red);
    title.setPosition(200, 50);

    sf::Text text("High score state", game->getFont());
    text.setColor(sf::Color::Red);
    text.setPosition(300, 300);

    game->getWindow().draw(text);
    game->getWindow().draw(title);
}