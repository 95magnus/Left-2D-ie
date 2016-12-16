//
// Created by Eivind Hystad on 17/11/2016.
//

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
    Projectile(sf::RenderWindow &window, sf::Texture &texture, sf::IntRect rect, int damage, float angle, float x, float y);
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

    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);

    const sf::Clock &getClock() const;

    void setClock(const sf::Clock &clock);

    const sf::Mouse &getMouse() const;

    void setMouse(const sf::Mouse &mouse);

    float getVelX() const;

    void setVelX(float velX);

    float getVelY() const;

    void setVelY(float velY);

    float getDiffX() const;

    void setDiffX(float diffX);

    float getDiffY() const;

    void setDiffY(float diffY);

    float getMagnitude() const;

    void setMagnitude(float magnitude);

    float getRndX() const;

    void setRndX(float rndX);

    float getRndY() const;

    void setRndY(float rndY);

    const sf::RectangleShape &getHitbox() const;

    void setHitbox(const sf::RectangleShape &hitbox);

private:
    sf::RectangleShape sprite;
    sf::RectangleShape hitbox;
    int damage, speed;
    float x, y;
    sf::Clock clock;
    sf::Mouse mouse;
    float velX, velY, diffX, diffY, magnitude, rndX, rndY;
};


#endif //LEFT2DIE_PROJECTILE_H
