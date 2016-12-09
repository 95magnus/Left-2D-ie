#ifndef LEFT2DIE_CAMERA_H
#define LEFT2DIE_CAMERA_H

#include "World.h"
#include "../entities/Player.h"

class Camera {
public:
    Camera(World &world, sf::Vector2f worldPos);
    Camera(World &world, Player &player);
    virtual ~Camera();

    void update(float deltaTime);

protected:
    sf::Vector2f worldPos;

    World &world;
    Player* player;
};

#endif //LEFT2DIE_CAMERA_H
