#include "StateSinglePlayer.h"

StateSinglePlayer::StateSinglePlayer(Game* game) : StateBase(game) {
    level = new Level("testLevel.l2d");
    pl = new Player;
    mb = new MessageBox(game->getWindow());
    players.push_back(pl->sprite.getPosition());
    zombie = new Enemy;
}

StateSinglePlayer::~StateSinglePlayer() {
    delete level;
    delete mb;
}

void StateSinglePlayer::update(float deltaTime) {
    zombie->update(players, deltaTime);
}

void StateSinglePlayer::draw() {
    level->draw(game->getWindow());
    mb->draw("Wave x - Good luck", 8, game->getWindow());
    pl->draw(game->getWindow());
    zombie->draw(game->getWindow());
}
