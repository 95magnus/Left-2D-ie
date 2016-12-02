//
// Created by Eivind Hystad on 30/11/2016.
//

#ifndef LEFT2DIE_ENEMY_H
#define LEFT2DIE_ENEMY_H


#include <math.h>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Player;

class Enemy{
public:
    sf::Texture texture;
    float velX, velY, diffX, diffY, magnitude;
    sf::RectangleShape sprite;
    sf::RectangleShape hitbox;
    sf::RectangleShape collisionBox;
    virtual ~Enemy();
    Enemy();
    void update(std::vector<Player*> players, float deltaTime);
    void draw(sf::RenderWindow &window);
private:
    sf::Vector2f target;
    int health;
    int damage;
    int speed;
};

#endif //LEFT2DIE_ENEMY_H
