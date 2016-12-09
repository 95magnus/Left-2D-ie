#include "Camera.h"

Camera::Camera(World &world, sf::Vector2f worldPos) : world(world) {
    this->worldPos = worldPos;

    player = nullptr;
}

Camera::Camera(World &world, Player &player) : world(world) {
    this->player = &player;
}

Camera::~Camera() {

}

void Camera::update(float deltaTime) {
    if (player)
        worldPos = player->getWorldPos();
}
