//
// Created by Eivind Hystad on 17/11/2016.
//


#include "Projectile.h"

Projectile::Projectile(sf::RenderWindow &window, sf::Texture &texture, sf::IntRect rect, int damage, float angle, float x, float y)
        : Entity(sf::Vector2f(x, y)) {
    sprite.setTexture(&texture);
    sprite.setTextureRect(rect);
    sprite.setSize(sf::Vector2f(rect.width, rect.height));
    sprite.setRotation(angle);
    this->damage = damage;
    this->x = x;
    this->y = y;
    this->damage = 10;
    speed = 450;
    sprite.setPosition(worldPos);
    sprite.setScale(0.1, 0.1);

    velX = -cos(angle * M_PI/180) * speed;
    velY = -sin(angle * M_PI/180) * speed;

    rndX = fRand();
    rndY = fRand();

    sprite.setOutlineColor(sf::Color::Cyan);
    sprite.setOutlineThickness(2);
}

Projectile::~Projectile() {

}

float Projectile::fRand()
{
    float rnd = rand() % -1000 + 1000;
    return rnd / 1000;
}

void Projectile::update(float deltaTime) {
    worldPos.x += velX * deltaTime * rndX;
    worldPos.y += velY * deltaTime * rndY;

    sprite.setPosition(worldPos);
}

void Projectile::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

const sf::RectangleShape &Projectile::getSprite() const {
    return sprite;
}

void Projectile::setSprite(const sf::RectangleShape &sprite) {
    this->sprite = sprite;
}

int Projectile::getDamage() const {
    return damage;
}

void Projectile::setDamage(int damage) {
    this->damage = damage;
}

int Projectile::getSpeed() const {
    return speed;
}

void Projectile::setSpeed(int speed) {
    Projectile::speed = speed;
}

float Projectile::getX() const {
    return x;
}

void Projectile::setX(float x) {
    this->x = x;
}

float Projectile::getY() const {
    return y;
}

void Projectile::setY(float y) {
    this->y = y;
}

const sf::Clock &Projectile::getClock() const {
    return clock;
}

void Projectile::setClock(const sf::Clock &clock) {
    this->clock = clock;
}

const sf::Mouse &Projectile::getMouse() const {
    return mouse;
}

void Projectile::setMouse(const sf::Mouse &mouse) {
    this->mouse = mouse;
}

float Projectile::getVelX() const {
    return velX;
}

void Projectile::setVelX(float velX) {
    this->velX = velX;
}

float Projectile::getVelY() const {
    return velY;
}

void Projectile::setVelY(float velY) {
    this->velY = velY;
}

float Projectile::getDiffX() const {
    return diffX;
}

void Projectile::setDiffX(float diffX) {
    this->diffX = diffX;
}

float Projectile::getDiffY() const {
    return diffY;
}

void Projectile::setDiffY(float diffY) {
    this->diffY = diffY;
}

float Projectile::getMagnitude() const {
    return magnitude;
}

void Projectile::setMagnitude(float magnitude) {
    this->magnitude = magnitude;
}

float Projectile::getRndX() const {
    return rndX;
}

void Projectile::setRndX(float rndX) {
    this->rndX = rndX;
}

float Projectile::getRndY() const {
    return rndY;
}

void Projectile::setRndY(float rndY) {
    this->rndY = rndY;
}

const sf::RectangleShape &Projectile::getHitbox() const {
    return hitbox;
}

void Projectile::setHitbox(const sf::RectangleShape &hitbox) {
    this->hitbox = hitbox;
}

