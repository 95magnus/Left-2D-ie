#include "StateSinglePlayer.h"
#include "../modules/Player.h"
#include "../modules/Enemy.h"

StateSinglePlayer::StateSinglePlayer(Game* game) : StateBase(game) {
    level = new Level(game->getWindow().getSize(), "testLevel.l2d");
    mb = new MessageBox(game->getWindow());

    window = &game->getWindow();
    view = &level->getView();
    //view->zoom(0.5f);

    //window->setView(*view);
    zombie = new Enemy();
}

StateSinglePlayer::~StateSinglePlayer() {
    delete level;
    delete mb;
    delete player;
    delete zombie;

    window->setView(window->getDefaultView());
}

void StateSinglePlayer::init() {
    player = new Player(game->getWindow(), game->getInputManager());
    players.push_back(player);
}

void StateSinglePlayer::update(float deltaTime) {
    level->update(deltaTime);
    player->update(deltaTime);
    player->move(deltaTime);

    level->translateMap(player->move(deltaTime));
    //zombie->update(players, deltaTime);
}

void StateSinglePlayer::draw() {
    level->draw(game->getWindow());
    mb->draw("Wave x - Good luck", 8, game->getWindow());
    player->draw(game->getWindow());
    zombie->draw(game->getWindow());
}
