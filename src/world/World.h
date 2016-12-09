#ifndef LEFT2DIE_WORLD_H
#define LEFT2DIE_WORLD_H

#include "../Game.h"
#include "../level/Level.h"
#include "../entities/Entity.h"

class Player;
class Level;

class World {
public:
    World(Game &game, String &levelFileName);
    virtual ~World();

    void update(float deltaTime);
    void draw(sf::RenderWindow &window);

protected:
    sf::Vector2f playerSpawn, playerPos;

    Game &game;
    Player *player;
    Level* level;
    sf::View* view;

    std::vector<Entity*> entities;
};

#endif //LEFT2DIE_WORLD_H
