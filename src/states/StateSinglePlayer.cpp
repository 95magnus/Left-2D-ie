#include "StateSinglePlayer.h"

StateSinglePlayer::StateSinglePlayer(Game* game) : StateBase(game) {
    level = new Level("testLevel.l2d");

    window = &game->getWindow();
    view = &level->getView();

    //view->zoom(0.5f);

    //window->setView(*view);
}

StateSinglePlayer::~StateSinglePlayer() {
    delete level;

    window->setView(window->getDefaultView());
}

void StateSinglePlayer::update(float deltaTime) {

}

void StateSinglePlayer::draw() {
    level->draw(game->getWindow());
}
