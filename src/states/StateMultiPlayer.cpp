#include "StateMultiPlayer.h"
#include "../world/World.h"

StateMultiPlayer::StateMultiPlayer(Game* game) : StateBase(game) {
    world = new World(*game, levelFileName);
}

StateMultiPlayer::~StateMultiPlayer() {
    delete world;
}

void StateMultiPlayer::update(float deltaTime) {
    world->update(deltaTime);
}

void StateMultiPlayer::draw(sf::RenderWindow &window) {
    world->draw(window);
}
