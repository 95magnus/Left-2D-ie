//
// Created by Eivind Hystad on 17/11/2016.
//

#include "Weapon.h"
#include <math.h>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

Weapon::Weapon() {
    //Load Texture
    if (!texture.loadFromFile("resources/textures/spritesheets/weapons.png")) {
        // Spilleren blir blå hvis bildet ikke blir lastet
        sprite.setFillColor(sf::Color::Green);
    } else {
        sprite.setTexture(&texture);
    }
    sprite.setPosition(100, 100);
    sprite.setSize(sf::Vector2f(80,80));
}

void Weapon::fire() {

}

void Weapon::moveUp(float dt) {
    sprite.move(0.f, 200 * dt * -1);
}

void Weapon::moveDown(float dt) {
    sprite.move(0.f, 200 * dt);
}

void Weapon::moveRight(float dt) {
    sprite.move(200 * dt, 0.f);
}

void Weapon::moveLeft(float dt) {
    sprite.move(200 * dt * -1, 0.f);
}

void Weapon::draw(sf::RenderWindow &window) {


    mousePos = sf::Mouse::getPosition();
    deltaX = sprite.getPosition().x - mousePos.x;
    deltaY = sprite.getPosition().y - mousePos.y;
    angleDegrees = atan2(deltaY, deltaX) * 180 / 3.1416;
    window.draw(sprite);
}

Weapon::~Weapon() {

}
