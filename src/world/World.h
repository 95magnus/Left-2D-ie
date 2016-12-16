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

    void handlePlayerMovement(float deltaTime);
    void spawnWave();
    void spawnWave(int wave);
    void goToShop();

    Player* getPlayer() { return player; }
    std::vector<Entity*>& getEntities() { return entities; }

protected:
    int minEnemyCount = 10, enemiesPerWave = 2, currentWave = 1;

    sf::Vector2f playerSpawn;

    Game &game;
    Player *player;
    Level* level;
    sf::View* view;

    sf::Vector2i prevPlayerTileIndex;

    std::vector<Entity*> entities;

    void updateEnemyToPlayerMovements();
    void updateBulletCollisions();

    sf::Vector2i findBestNeighborTile(sf::Vector2i tileIndex);

    static bool entityDrawOrder(Entity* e1, Entity* e2);

    void setMovementAtTile(sf::Vector2i tileIndex, int movements);
};

#endif //LEFT2DIE_WORLD_H
