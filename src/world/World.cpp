#include "World.h"
#include "../entities/Player.h"
#include "../entities/enemies/Enemy.h"
#include "../entities/enemies/CrawlingZombie.h"

World::World(Game &game, String &levelFileName) : game(game) {
    view = new sf::View(sf::FloatRect(0, 0, game.getWindow().getSize().x, game.getWindow().getSize().y));
    level = new Level(game.getWindow().getSize(), levelFileName);
    playerSpawn = sf::Vector2f(32 * 10, 32 * 10);
    player =  new Player(game.getWindow(), *view, game.getInputManager(), playerSpawn);
    playerPos = player->getWorldPos();

    // Doesn't work: entities.push_back((Entity*) player);
    // Suggested by CLion, works for some reason:
    entities.push_back((Entity* &&) player);

    for (int i = 0; i < 10; i++) {
        float randX = (float) (rand() / RAND_MAX) + 1 + i;
        float randY = (float) (rand() / RAND_MAX) + 1 + i;

        entities.push_back((Entity*) new Enemy(sf::Vector2f(randX * 400, randY * 400)));
    }

    for (int i = 0; i < 5; i++) {
        float randX = (float) (rand() / RAND_MAX) + 1 + i;
        float randY = (float) (rand() / RAND_MAX) + 1 + i;

        entities.push_back((CrawlingZombie*) new CrawlingZombie(sf::Vector2f(randY * 400, randX * 400)));
    }

}

World::~World() {
    auto entity = entities.begin();
    while (entity != entities.end()) {
        entity = entities.erase(entity);
    }
}

void World::update(float deltaTime) {
    for (auto &entity : entities) {
        entity->update(deltaTime);

        if (Enemy* enemy = dynamic_cast<Enemy*>(entity)) {
            enemy->setTarget(player->getWorldPos());
        }
    }

    view->move(player->move(deltaTime));
    view->setCenter(player->getWorldPos());

    for (int e = 1; e < entities.size(); e++) {
        if (abs(static_cast<Enemy*>(entities[e])->getWorldPos().x - (static_cast<Player*>(entities[0]))->getWorldPos().x) <= 35
        && (abs(static_cast<Enemy*>(entities[e])->getWorldPos().y - (static_cast<Player*>(entities[0]))->getWorldPos().y) <= 35)){
            static_cast<Enemy*>(entities[e])->dealDamage((static_cast<Player*>(entities[0])));
        }
    }
}

void World::draw(sf::RenderWindow &window) {
    window.setView(*view);

    level->draw(window);

    for (auto &entity : entities)
        entity->draw(window);

    window.setView(window.getDefaultView());
}