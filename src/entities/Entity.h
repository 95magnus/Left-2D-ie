#ifndef LEFT2DIE_ENTITY_H
#define LEFT2DIE_ENTITY_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Entity {
public:
    Entity(sf::Vector2f worldPos) : worldPos(worldPos) {}
    virtual ~Entity() {}

    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;

    sf::Vector2f getWorldPos() { return worldPos; }
    void setWorldPos(sf::Vector2f pos) { worldPos = pos; }
    void setWorldPos(float x, float y) { worldPos = sf::Vector2f(x, y); }

protected:
    sf::Vector2f worldPos;
};

#endif //LEFT2DIE_ENTITY_H
