#include "StateBase.h"

StateBase::StateBase(Game* game) {
    this->game = game;

    paused = false;
}