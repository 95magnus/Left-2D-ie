//
// Created by Eivind Hystad on 14/10/2016.
//

#include "Player.h"

// Constructor
Player::Player() {
    health = 100;
    armor = 0;
    speed = 200;
    kills = 0;
    score = 0;
    money = 0;
    sprite.setSize(sf::Vector2f(30, 100));

    //Load Texture
    sf::Texture texture;
    texture.setSmooth(false);
    texture.setRepeated(false);
    if (!texture.loadFromFile("Assets/img/player1.bmp")) {
        // Spilleren blir blå hvis bildet ikke blir lastet
        sprite.setFillColor(sf::Color::Blue);
    } else {
        sprite.setTexture(&texture);
    }

    // Hitboxen blir like brei som karakten, og 1/3 av høyden
    hitbox.setSize(sf::Vector2f(sprite.getSize().x, sprite.getSize().y / 3));
    // Hitboxen ligger rundt karakterens føtter.
    hitbox.setPosition(sprite.getPosition().x, sprite.getPosition().y + sprite.getSize().y - hitbox.getSize().y);
}

// Deconstructor
Player::~Player() {

}

// Action functions
void Player::moveUp(float dt) {
    sprite.move(0.f, speed * dt * -1);
    hitbox.move(0.f, speed * dt * -1);
}

void Player::moveDown(float dt) {
    sprite.move(0.f, speed * dt);
    hitbox.move(0.f, speed * dt);
}

void Player::moveRight(float dt) {
    sprite.move(speed * dt, 0.f);
    hitbox.move(speed * dt, 0.f);
}

void Player::moveLeft(float dt) {
    sprite.move(speed * dt * -1, 0.f);
    hitbox.move(speed * dt * -1, 0.f);
}

void Player::death() {
    // TODO: Legge til dødsanimasjon når health = 0?
    // TODO: (kanskje player faller i bakken og blinker i 3 sek så forsvinner den slik som på gamle spill)
    // Kaller dekonstruktøren for player
    Player::~Player();
}

// Getters & setters
int Player::getHealth() const {
    return health;
}

void Player::setHealth(int health) {
    Player::health = health;
}

int Player::getSpeed() const {
    return speed;
}

void Player::setSpeed(int speed) {
    Player::speed = speed;
}

int Player::getScore() const {
    return score;
}

void Player::setScore(int score) {
    Player::score = score;
}

int Player::getMoney() const {
    return money;
}

void Player::setMoney(int money) {
    Player::money = money;
}

int Player::getArmor() const {
    return armor;
}

void Player::setArmor(int armor) {
    Player::armor = armor;
}

int Player::getKills() const {
    return kills;
}

void Player::setKills(int kills) {
    Player::kills = kills;
}
