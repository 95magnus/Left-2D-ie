#include "StateSinglePlayer.h"
#include "../modules/MessageBox.h"

StateSinglePlayer::StateSinglePlayer(Game* game) : StateBase(game) {
    level = new Level("testLevel.l2d");
    mb = new MessageBox(game->getWindow());

    window = &game->getWindow();
    view = &level->getView();
    //view->zoom(0.5f);

    //window->setView(*view);
}

StateSinglePlayer::~StateSinglePlayer() {
    delete level;
    delete mb;
    //delete player;

    window->setView(window->getDefaultView());
}

void StateSinglePlayer::init() {
    player = new Player(&game->getInputManager());
}

void StateSinglePlayer::update(float deltaTime) {
    level->update(deltaTime);
    player->update(deltaTime);

    player->move(deltaTime);
}

void StateSinglePlayer::draw() {
    level->draw(game->getWindow());
    mb->draw("Wave x - Good luck", 8, game->getWindow());
    player->draw(game->getWindow());
}
