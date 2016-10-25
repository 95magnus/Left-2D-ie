#include "InputObserver.h"
#include "InputManager.h"

InputObserver::InputObserver(InputManager* inputManager) {
    this->inputManager = inputManager;

    inputManager->addObserver(this);
}