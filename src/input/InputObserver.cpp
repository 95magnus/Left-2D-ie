#include "InputObserver.h"
#include "InputManager.h"

InputObserver::InputObserver(InputManager &inputManager) : inputManager(inputManager) {
    inputManager.addObserver(this);
}