#include "PlayerController.h"

PlayerController::PlayerController(InputManager &inputManager) : InputObserver(inputManager){}

PlayerController::PlayerController(InputManager &inputManager, int joystickID)
        : PlayerController(inputManager){
    this->joystickID = joystickID;

    usingController = true;
}

PlayerController::~PlayerController() {

}

void PlayerController::update(float deltaTime) {
    pollJoystick();
}

void PlayerController::actionMove(sf::Vector2f direction) {
    this->moveDirection = direction;
}

void PlayerController::pollJoystick() {
    // TODO: Handle more than one joystick (multiplayer/co-op support)
    if (!inputManager.isJoystickConnected(joystickID))
        return;

    moveDirection = inputManager.getStickPosition(joystickID, sf::Joystick::Axis::X, sf::Joystick::Axis::Y);
    viewingDirection = inputManager.getStickPosition(joystickID, sf::Joystick::Axis::U, sf::Joystick::Axis::V);
    shooting = inputManager.isTriggerPressed(joystickID, sf::Joystick::Axis::R);
}

void PlayerController::setJoystickID(int joystickID) {
    this->joystickID = joystickID;
}