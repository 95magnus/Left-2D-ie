#include "StateBase.h"

StateBase::StateBase(Game* game) {
    this->game = game;
    paused = false;
    desktop = new sfg::Desktop();
}

StateBase::~StateBase() {
    delete desktop;
}

void StateBase::updateDesktop() {
    desktop->Update(timer.getElapsedTime().asMilliseconds());
    timer.restart();
}