#include "StateGameOver.h"

StateGameOver::StateGameOver(Game *game) : StateBase(game) {
    ResourceLoader loader("resources/");

    graveStone.setTexture(&loader.loadTexture("gravestone.png"));
    graveStone.setPosition(350, 300);
    graveStone.setSize(sf::Vector2f(330, 225));

    gameOverTitle = sf::Text("Game Over!", game->getFont(), 100);
    gameOverTitle.setPosition(330, 80);
    gameOverTitle.setColor(sf::Color::Red);
    gameOverTitle.setStyle(sf::Text::Bold);

    score = sf::Text("Score: 0", game->getFont(), 64);
    score.setPosition(350, 560);
    score.setColor(sf::Color::White);

}

StateGameOver::~StateGameOver() {

}

void StateGameOver::update(float deltaTime) {

}

void StateGameOver::draw(sf::RenderWindow &window) {
    window.draw(gameOverTitle);
    window.draw(graveStone);
    window.draw(score);
}

void StateGameOver::setScore(int score) {
    this->score.setString("Score: " + score);
}
