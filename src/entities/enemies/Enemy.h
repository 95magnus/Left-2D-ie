//
// Created by Eivind Hystad on 30/11/2016.
//

#ifndef LEFT2DIE_ENEMY_H
#define LEFT2DIE_ENEMY_H


#include <math.h>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Player.h"

class Player;

class Enemy : public Entity {
public:
    Enemy(sf::Vector2f spawnPos);
    virtual ~Enemy();

    sf::Texture texture;
    float velX, velY, diffX, diffY, magnitude;
    sf::RectangleShape sprite;
    sf::RectangleShape hitbox;
    sf::RectangleShape collisionBox;

    void update(float deltaTime);
    void update(std::vector<sf::Vector2f> players, float deltaTime);
    void draw(sf::RenderWindow &window);

    void translate(sf::Vector2f offset);
    void animationCycler(float interval);
    void getHit(int damage);
    sf::IntRect rect[3] = {{335, 0, 300, 600},
                                     {640, 0, 300, 600},
                                     {0, 0, 330, 600}};

    int getHealth() const;

    void setHealth(int health);

    void setTarget(sf::Vector2f pos);

private:
    sf::RectangleShape healthBar;
    sf::RectangleShape hpBarBG;
    sf::Clock cycleClock;

    sf::Vector2f target;

    int health;
    int maxHealth;
    int damage;
    int speed;
    int xOffs, yOffs;
    int rewardPoints;
    bool goingRight;
    int hit;
    sf::Vector2f prev;
};

#endif //LEFT2DIE_ENEMY_H
