#ifndef LEFT2DIE_PROJECTILE_H
#define LEFT2DIE_PROJECTILE_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include <math.h>
#include "Entity.h"

class Projectile : public Entity {
public:
    Projectile(sf::RenderWindow &window, sf::Texture &texture, sf::IntRect rect, int damage, int speed, bool spray, float angle, float x, float y);
    ~Projectile();

    float fRand();

    void update(float deltaTime);
    void draw(sf::RenderWindow &window);

    const sf::RectangleShape &getSprite() const;

    sf::FloatRect getBounds() { return sprite.getGlobalBounds(); }

    void setSprite(const sf::RectangleShape &sprite);

    int getDamage() const;
    void setDamage(int damage);

    int getSpeed() const;
    void setSpeed(int speed);

    const sf::Clock &getClock() const;
    void setClock(const sf::Clock &clock);

    const sf::Mouse &getMouse() const;
    void setMouse(const sf::Mouse &mouse);

private:
    sf::RectangleShape sprite;
    bool spray;
    int damage, speed;
    float x, y;
    sf::Clock clock;
    sf::Mouse mouse;
    float velX, velY, rndX, rndY;
};

#endif //LEFT2DIE_PROJECTILE_H
