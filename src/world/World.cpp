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

    // Doesn't work: entities.push_back((Entity*) player);
    // Suggested by CLion, works for some reason:
    entities.push_back((Entity* &&) player);

    for (int i = 0; i < 30; i++) {
        float randX = (float) (rand() % 600);
        float randY = (float) (rand() % 600);

        entities.push_back((Entity*) new Enemy(sf::Vector2f(randX, randY)));
    }
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
            auto enemyTileIndex = level->worldCoordToTileIndex(enemy->getWorldPos());
            auto targetTile = findBestNeighborTile(enemyTileIndex);

            if (targetTile == sf::Vector2i(-1, -1))
                continue;

            enemy->setTarget(targetTile * (int)level->tileSize);
        }
    }
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

            auto tile = tileMap->at(current.y).at(current.x);

            if (tile->getMovements() != -1)
                tile->incrementCost();
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

    // Currently best tile with least movements found
    sf::Vector2i bestTile(-1, -1);
    int bestMovements = INFINITY;

    for (int y = yMin; y < yMax; y++) {
        for (int x = xMin; x < xMax; x++) {
            // Ignore original location tile
            if (sf::Vector2i(x, y) == tileIndex)
                continue;

            // First loop, assign neighbor
            if (bestTile == sf::Vector2i(-1, -1)){
                bestTile = sf::Vector2i(x, y);
                bestMovements = tileMap->at(y).at(x)->getMovements();
                continue;
            }

            int movements = tileMap->at(y).at(x)->getMovements();

            // Tile is solid, ignore
            if (movements == -1)
                continue;

            if (movements < bestMovements) {
                bestMovements = movements;
                bestTile = sf::Vector2i(x, y);
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(Key::Space))
        std::cout << bestTile.x << ", " << bestTile.y << " - " << bestMovements << std::endl;

    return bestTile;
}

bool World::entityDrawOrder(Entity *e1, Entity *e2) {
    int y1 = e1->getWorldPos().y;
    int y2 = e2->getWorldPos().y;

    return y1 < y2;
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


