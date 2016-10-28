#include "StatePlayGame.h"

StatePlayGame::StatePlayGame(Game* game) : StateBase(game) {

}

StatePlayGame::~StatePlayGame() {

}

void StatePlayGame::update() {

}

void StatePlayGame::draw() {
//    sf::Text title("Left[2D]ie", game->getFont(), 100);
//    title.setFillColor(sf::Color::Red);
//    title.setPosition(200, 50);

    sf::Text text("Play", game->getFont());
    text.setFillColor(sf::Color::Red);
    text.setPosition(600, 200);

    game->getWindow().draw(text);
//    game->getWindow().draw(title);
}