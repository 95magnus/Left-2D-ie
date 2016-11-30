#include "PlayerController.h"

PlayerController::PlayerController(InputManager &inputManager) : InputObserver(inputManager){
    this->joystickID = 0;
}

PlayerController::PlayerController(InputManager &inputManager, int joystickID)
        : PlayerController(inputManager){
    this->joystickID = joystickID;
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
    //if (inputManager->connectedJoystickCount() == 0)
    if (!inputManager.isJoystickConnected(joystickID))
        return;

    moveDirection = inputManager.getStickPosition(joystickID, sf::Joystick::Axis::X, sf::Joystick::Axis::Y);
}

void PlayerController::setJoystickID(int joystickID) {
    this->joystickID = joystickID;
}