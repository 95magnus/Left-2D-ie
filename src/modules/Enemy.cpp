//
// Created by Eivind Hystad on 30/11/2016.
//

#include "Enemy.h"
//#include "Player.h"

Enemy::Enemy() {
    // Laster inn texture
    if (!texture.loadFromFile("resources/textures/spritesheets/zombie.png")) {
        printf("Couldn't load zombie texture.");
        sprite.setFillColor(sf::Color::Blue);
    } else {
        sprite.setTexture(&texture);
    }
    health = 100;
    damage = 20;
    speed = 10;

    sprite.setSize(sf::Vector2f(100, 100));
}

Enemy::~Enemy() {

}

void Enemy::update(std::vector<Player*> players, float deltaTime) {
    target.x = 9999;
    target.y = 9999;
/*
    // Går gjennom lista med spillerenes posisjoner for å finne den nærmeste
    for (auto it = players.begin(); it != players.end(); it++) {
        if (abs(target.x - it->x) < target.x && abs(target.y - it->y)) {
            target = *it;
        }
    }
*/
    // Under får zombien en retning å gå, den vil bevege seg likt som prosjektilene
    diffX = target.x - sprite.getPosition().x;
    diffY = target.y - sprite.getPosition().y;
    magnitude = sqrtf(diffX*diffX + diffY*diffY);
    velX = diffX/magnitude*speed;
    velY = diffY/magnitude*speed;
    sprite.move(velX*deltaTime, velY*deltaTime);
    hitbox.setPosition(sprite.getPosition());
}

void Enemy::draw(sf::RenderWindow &window) {
    sprite.setPosition(100, 100);
    window.draw(sprite);
    window.draw(hitbox);
    window.draw(collisionBox);
}