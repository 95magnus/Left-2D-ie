#include "StateSinglePlayer.h"
#include "../modules/MessageBox.h"

StateSinglePlayer::StateSinglePlayer(Game* game) : StateBase(game) {
    level = new Level("testLevel.l2d");

    mb = new MessageBox(game->getWindow());
}

StateSinglePlayer::~StateSinglePlayer() {
    delete level;
    delete mb;
}

void StateSinglePlayer::update(float deltaTime) {

}

void StateSinglePlayer::draw() {
    level->draw(game->getWindow());
    mb->draw("Wave x - Good luck", 8, game->getWindow());
}
