//
// Created by Eivind Hystad on 17/11/2016.
//

#ifndef LEFT2DIE_WEAPON_H
#define LEFT2DIE_WEAPON_H


#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

class Weapon {
public:
    Weapon();

    virtual ~Weapon();
    void moveUp(float dt);
    void moveDown(float dt);
    void moveRight(float dt);
    void moveLeft(float dt);
    void fire();
    void draw(sf::RenderWindow &window);
    double angleDegrees;
    float deltaY;
    float deltaX;
    enum Type {Primary, Secondary, Special};
    enum Direction {Left, Right, Up, Down};
    Direction currentDir;
    Type type;
    sf::Texture texture;
    sf::RectangleShape sprite;
    sf::Vector2i mousePos;
};


#endif //LEFT2DIE_WEAPON_H
