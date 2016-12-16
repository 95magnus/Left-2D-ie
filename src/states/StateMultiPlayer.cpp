#include <SFML/Window/Keyboard.hpp>
#include "StateMultiPlayer.h"
#include "../world/World.h"

StateMultiPlayer::StateMultiPlayer(Game* game) : StateBase(game) {
    world = new World(*game, levelFileName);

    screenShadow.setSize(game->getWindowSize());
    screenShadow.setFillColor(sf::Color(0, 0, 0, 128));

    pauseText = sf::Text("Game paused!\n\nPress ESC to resume.", game->getFont(), 80);
    pauseText.setPosition(250, 230);
    pauseText.setColor(sf::Color::White);
}

StateMultiPlayer::~StateMultiPlayer() {
    delete world;
}

void StateMultiPlayer::update(float deltaTime) {
    if (!paused)
        world->update(deltaTime);
}

void StateMultiPlayer::draw(sf::RenderWindow &window) {
    world->draw(window);

    if (paused) {
        window.draw(screenShadow);
        window.draw(pauseText);
    }
}
