#include "StateSinglePlayer.h"

StateSinglePlayer::StateSinglePlayer(Game* game) : StateBase(game) {
    level = new Level("testLevel.l2d");
}

StateSinglePlayer::~StateSinglePlayer() {
    delete level;
}

void StateSinglePlayer::update(float deltaTime) {

}

void StateSinglePlayer::draw() {
    level->draw(game->getWindow());

}
