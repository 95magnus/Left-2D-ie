#include <queue>
#include "World.h"
#include "../entities/Player.h"
#include "../entities/enemies/Enemy.h"

World::World(Game &game, String &levelFileName) : game(game) {
    view = new sf::View(sf::FloatRect(0, 0, game.getWindow().getSize().x, game.getWindow().getSize().y));
    level = new Level(game.getWindow().getSize(), levelFileName);
    playerSpawn = sf::Vector2f(32 * 6, 32 * 6);
    player =  new Player(game.getWindow(), *view, game.getInputManager(), playerSpawn);
    prevPlayerTileIndex = level->worldCoordToTileIndex(player->getWorldPos());

    entities.push_back((Entity* &&) player);

    spawnWave(currentWave++);
    updateEnemyToPlayerMovements();
}

World::~World() {
    auto entity = entities.begin();
    while (entity != entities.end()) {
        entity = entities.erase(entity);
    }
}

void World::update(float deltaTime) {
    handlePlayerMovement(deltaTime);

    for (auto &entity : entities) {
        entity->update(deltaTime);

        if (Enemy* enemy = dynamic_cast<Enemy*>(entity)) {
            sf::Vector2i pos = level->worldCoordToTileIndex(enemy->getWorldPos());

            if (pos == sf::Vector2i(-1, -1))
                continue;

            auto tile = level->getTileMap().at(pos.y).at(pos.x);

            if (tile->getMovements() != -1)
                tile->incrementCost();

            if (!enemy->requestingNewTarget())
                continue;

            auto enemyTileIndex = level->worldCoordToTileIndex(enemy->getWorldPos());
            auto targetTile = findBestNeighborTile(enemyTileIndex);

            if (targetTile == sf::Vector2i(-1, -1))
                continue;

            enemy->setTarget(targetTile * (int)level->tileSize);
        }
    }

    updateBulletCollisions();

}

void World::draw(sf::RenderWindow &window) {
    window.setView(*view);

    level->draw(window);

    // Sort entities by draw order (position on y-axis)
    std::sort(entities.begin(), entities.end(), entityDrawOrder);

    for (auto &entity : entities)
        entity->draw(window);

    window.setView(window.getDefaultView());
}

void World::handlePlayerMovement(float deltaTime) {
    view->move(player->move(deltaTime));
    view->setCenter(player->getWorldPos());

    sf::Vector2i playerTileIndex = level->worldCoordToTileIndex(player->getWorldPos());

    if (playerTileIndex == prevPlayerTileIndex)
        return;

    prevPlayerTileIndex = playerTileIndex;

    if (playerTileIndex != sf::Vector2i(-1, -1) && false) {
        TileMap &tilesSurroundingPlayer = level->getSurroundingTiles(playerTileIndex, 1);

        for (auto &tileRow : tilesSurroundingPlayer) {
            for (auto &tile : tileRow) {
                if (static_cast<TileBase*>(tile)->isSolid()) {
                    sf::FloatRect pRect = player->getBounds();
                    sf::FloatRect tRect = static_cast<TileBase *>(tile)->getBounds();

                    sf::Vector2f pCenter(pRect.left + (pRect.width / 2.0f), pRect.top + (pRect.height / 2.0f));
                    sf::Vector2f tCenter(tRect.left + (tRect.width / 2.0f), tRect.top + (tRect.height / 2.0f));

                    float wy = (pRect.width + tRect.width) * (tCenter.y - pCenter.y);
                    float hx = (pRect.height + tRect.height) * (tCenter.x - pCenter.x);

                    float xDist = pCenter.x - tCenter.x;
                    float yDist = pCenter.y - tCenter.y;
                    float minWidth = (pRect.width / 2.0f) + (tRect.width / 2.0f);
                    float minHeight = (pRect.height / 2.0f) + (tRect.height / 2.0f);

                    if (abs(xDist) >= minWidth || abs(yDist) >= minHeight)
                        continue;

                    if (wy > hx) {
                        if (wy > -hx) {
                            // Top
                            player->setWorldPos(pCenter.x, tCenter.y - minHeight);
                        } else {
                            // Left
                            player->setWorldPos(tCenter.x - minWidth, pCenter.y);
                        }
                    } else {
                        if (wy > -hx) {
                            // Bottom
                            player->setWorldPos(pCenter.x, tCenter.y + minHeight);
                        } else {
                            // Right
                            player->setWorldPos(tCenter.x + minWidth, pCenter.y);
                        }
                    }

                    /*
                    float xDist = pCenter.x - tCenter.x;
                    float yDist = pCenter.y - tCenter.y;
                    float minWidth = (pRect.width / 2.0f) + (tRect.width / 2.0f);
                    float minHeight = (pRect.height / 2.0f) + (tRect.height / 2.0f);

                    if (abs(xDist) >= minWidth || abs(yDist) >= minHeight)
                        continue;

                    sf::Vector2f tilePenetration;
                    if (xDist > yDist) {
                        //
                    } else {

                    }

                    tilePenetration.x = xDist > 0 ? minWidth - xDist : -minWidth - xDist;
                    tilePenetration.y = yDist > 0 ? minHeight - yDist : -minHeight - yDist;

                    player->setWorldPos(player->getWorldPos() + tilePenetration);
                    */
                }
            }
        }
    }

    updateEnemyToPlayerMovements();
}

void World::updateEnemyToPlayerMovements() {
    sf::Vector2i playerTileIndex = level->worldCoordToTileIndex(player->getWorldPos());
    TileMap* tileMap = &level->getTileMap();

    for (auto &row : *tileMap)
        for (auto &tile: row)
            tile->resetMovements();

    std::queue<sf::Vector2i> tileIndexQueue;
    std::vector<sf::Vector2i> processed;
    tileIndexQueue.push(playerTileIndex);
    processed.push_back(playerTileIndex);

    setMovementAtTile(playerTileIndex, 0);

    int currentMovement;
    sf::Vector2i current;
    while (!tileIndexQueue.empty()) {
        current = tileIndexQueue.front();
        tileIndexQueue.pop();

        if (current == sf::Vector2i(-1, -1))
            continue;

        auto movements = tileMap->at(current.y).at(current.x)->getMovements();

        // Check if tile is solid, if so, keep movements from previous tile
        currentMovement = (movements == -1) ? currentMovement : movements;

        sf::Vector2i left(current.x - 1, current.y);
        sf::Vector2i right(current.x + 1, current.y);
        sf::Vector2i over(current.x, current.y - 1);
        sf::Vector2i under(current.x, current.y + 1);

        // Add neighbors to tileQueue
        if (left.x >= 0 && !tileMap->at(left.y).at(left.x)->isMovementsUpdated()) {
            tileIndexQueue.push(left);
            setMovementAtTile(left, currentMovement + 1);
        }

        if (right.x < level->levelWidth && !tileMap->at(right.y).at(right.x)->isMovementsUpdated()) {
            tileIndexQueue.push(right);
            setMovementAtTile(right, currentMovement + 1);
        }

        if (over.y >= 0 && !tileMap->at(over.y).at(over.x)->isMovementsUpdated()) {
            tileIndexQueue.push(over);
            setMovementAtTile(over, currentMovement + 1);
        }

        if (under.y < level->levelHeight && !tileMap->at(under.y).at(under.x)->isMovementsUpdated()) {
            tileIndexQueue.push(under);
            setMovementAtTile(under, currentMovement + 1);
        }
    }

    // The tile an enemy is standing on has an extra movement cost
    // Should cause enemies to spread out more and possibly take an alternate route
    for (auto &entity: entities) {
        if (auto enemy = dynamic_cast<Enemy*>(entity)) {
            sf::Vector2i pos = level->worldCoordToTileIndex(enemy->getWorldPos());

            if (pos == sf::Vector2i(-1, -1))
                continue;

            auto tile = tileMap->at(pos.y).at(pos.x);

//            if (tile->getMovements() != -1)
  //              tile->incrementCost();
        }
    }

    for (auto &row : level->getTileMap()){
        for (auto &tile : row) {
            std::cout << tile->getMovements() << "\t";
        }
        std::cout << std::endl;
    }

    std::cout << "--------------------------------------------------------" << std::endl;

}

sf::Vector2i World::findBestNeighborTile(sf::Vector2i tileIndex) {
    if (tileIndex == sf::Vector2i(-1, -1))
        return tileIndex;

    auto tileMap = &level->getTileMap();

    // Map border checks
    int xMin = std::max(0, tileIndex.x - 1);
    int xMax = std::min(level->levelWidth, tileIndex.x + 1);
    int yMin = std::max(0, tileIndex.y - 1);
    int yMax = std::min(level->levelHeight, tileIndex.y + 1);

    // Currently best tile with least movements found, start with origin tile
    sf::Vector2i bestTile = tileIndex;
    int bestMovements = INFINITY;//tileMap->at(bestTile.y).at(bestTile.x)->getMovements();

    for (int y = yMin; y < yMax; y++) {
        for (int x = xMin; x < xMax; x++) {
            // Ignore original location tile
            //if (sf::Vector2i(x, y) == tileIndex)
             //   continue;

            int movements = tileMap->at(y).at(x)->getMovements();

            if (movements > -1 && movements < bestMovements) {
                bestMovements = movements;
                bestTile = sf::Vector2i(x, y);
            }
        }
    }

    /*
    if (sf::Keyboard::isKeyPressed(Key::Space))
        std::cout << bestTile.x << ", " << bestTile.y << " - " << bestMovements << std::endl;
*/

    return bestTile;
}

void World::setMovementAtTile(sf::Vector2i tileIndex, int movements) {
    if (tileIndex == sf::Vector2i(-1, -1))
        return;

    auto tile = level->getTileMap().at(tileIndex.y).at(tileIndex.x);

    if (!tile->isSolid())
        tile->setMovements(movements);
    else
        tile->setMovements(-1);
}

void World::updateBulletCollisions() {
    auto  projectiles = &player->getProjectiles();
    std::vector<Enemy*> enemies;

    for (auto &entity : entities) {
        if (auto enemy = dynamic_cast<Enemy*>(entity)) {
            enemies.push_back(enemy);
        }
    }

    for (auto &projectile : *projectiles) {
        for (auto &enemy : enemies) {
            auto projectileBounds = projectile->getSprite().getGlobalBounds();
            auto enemyBounds = enemy->sprite.getGlobalBounds();

            if (projectileBounds.intersects(enemyBounds)) {
                enemy->getHit(projectile->getDamage());
                projectile->setDead();

                if (enemy->getHealth() <= 0)
                    enemy->setDead();
            }
        }

        sf::Vector2i tilePos = level->worldCoordToTileIndex(projectile->getWorldPos());

        if (tilePos == sf::Vector2i(-1, -1)
            || tilePos.x > level->levelWidth
            || tilePos.y > level->levelHeight
            || tilePos.x < 0
            || tilePos.y < 0)
            continue;

        auto projectileBounds = projectile->getSprite().getGlobalBounds();
        auto projectileTileIndex = level->worldCoordToTileIndex(projectile->getWorldPos());
        auto surroundingTiles = &level->getSurroundingTiles(projectileTileIndex, 1);

        for (auto &tileRow : *surroundingTiles) {
            for (auto &tile : tileRow) {
                if (tile->isSolid() && projectileBounds.intersects(tile->getBounds()))
                    projectile->setDead();
            }
        }
    }

    for (int i = 0; i < enemies.size(); i++) {
        if (enemies[i]->isDead())
            entities.erase(std::remove(entities.begin(), entities.end(), enemies[i]), entities.end());
    }

    for (int i = 0; i < projectiles->size(); i++) {
        if (projectiles->at(i)->isDead())
            projectiles->erase(projectiles->begin() + i);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        std::cout << "";


    /*
    // TODO: Optimize search
    if (!enemies.empty() && !projectiles.empty()) {
        for (int i = 0; i < projectiles.size(); i++) {
            for (int j = 0; j < enemies.size(); j++) {
                if (projectiles[i]->getSprite().getPosition().x + 20 >= enemies[j]->sprite.getPosition().x
                    && projectiles[i]->getSprite().getPosition().x + 20
                       <= enemies[j]->sprite.getPosition().x + (enemies[j]->hitbox.getSize().x*0.2)
                    && projectiles[i]->getSprite().getPosition().y
                       >= enemies[j]->sprite.getPosition().y
                    && projectiles[i]->getSprite().getPosition().y
                       <= enemies[j]->sprite.getPosition().y + (enemies[j]->hitbox.getSize().y)*0.2) {

                    enemies[j]->getHit(projectiles[i]->getDamage());
                    projectiles.erase(projectiles.begin() + i);
                    i++;
                }
            }
        }
    }

    auto enemy = enemies.begin();
    while (enemy != enemies.end()) {
        if ((*enemy)->getHealth() <= 0) {
            enemy = enemies.erase(enemy);
        } else {
            ++enemy;
        }
    }


    auto projectile = projectiles.begin();
    while(projectile != projectiles.end()) {
        sf::Vector2i tilePos = level->worldCoordToTileIndex((*projectile)->getWorldPos());

        if (tilePos != sf::Vector2i(-1, -1)) {
            ++projectile;
            continue;
        }

        auto projectileBounds = (*projectile)->getSprite().getLocalBounds();
        auto tile = level->getTileMap().at(tilePos.y).at(tilePos.x);

        // Projectile collided with solid tile
        if (tile->isSolid() && projectileBounds.intersects(tile->getBounds())){
            projectile = projectiles.erase(projectile);
        } else {
            ++projectile;
        }
    }
     */
}

void World::spawnWave(int wave) {
    for (int i = 0; i < minEnemyCount + wave * enemiesPerWave; i++) {
        float x = rand() % ((level->levelWidth - 2) * level->tileSize) + level->tileSize;
        float y = rand() % ((level->levelHeight - 2) * level->tileSize) + level->tileSize;

        entities.push_back(new Enemy(sf::Vector2f(x, y)));
    }
}

bool World::entityDrawOrder(Entity* e1, Entity* e2) {
    int y1 = e1->getWorldPos().y;
    int y2 = e2->getWorldPos().y;

    return y1 < y2;
}


