//
// Created by Eivind Hystad on 17/11/2016.
//


#include "Projectile.h"

Projectile::Projectile(sf::RenderWindow &window, sf::Texture &texture, sf::IntRect rect, int damage, int speed, bool spray, float angle, float x, float y)
        : Entity(sf::Vector2f(x, y)) {
    sprite.setTexture(&texture);
    sprite.setTextureRect(rect);
    sprite.setSize(sf::Vector2f(rect.width, rect.height));
    sprite.setRotation(angle);
    this->damage = damage;
    this->x = x;
    this->y = y;
    this->damage = 10;
    this->increasedDamage = 0;
    this->increasedFireRate = 0;
    this->speed = speed;
    this->spray = spray;
    sprite.setPosition(x, y);
    sprite.setScale(0.1, 0.1);
    diffX = mouse.getPosition(window).x - x;
    diffY = mouse.getPosition(window).y - y;
    magnitude = sqrtf(diffX*diffX + diffY*diffY);
    //velX = diffX/magnitude*speed;
    //velY = diffY/magnitude*speed;


    velX = -cos(angle * M_PI/180) * speed;
    velY = -sin(angle * M_PI/180) * speed;

    rndX = fRand();
    rndY = fRand();
    hitbox.setSize(sprite.getSize());
    hitbox.setScale(sprite.getScale());
    hitbox.setPosition(sprite.getPosition());
    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(3);
}

float Projectile::fRand()
{
    if (!spray) {
        return 1;
    }
    float rnd = (float) (rand() % -100 + 100);
    return rnd / 100.0f;
}

Projectile::~Projectile() {

}

void Projectile::update(float deltaTime) {
    sf::Vector2f vel(velX * rndX, velY * rndY);
    float length = sqrt(vel.x * vel.x + vel.y * vel.y);
    vel /= length;

    x += vel.x * speed * deltaTime;
    y += vel.y * speed * deltaTime;
    sprite.setPosition(x, y);
    hitbox.setPosition(sprite.getPosition());
}

const sf::RectangleShape &Projectile::getSprite() const {
    return sprite;
}

void Projectile::setSprite(const sf::RectangleShape &sprite) {
    Projectile::sprite = sprite;
}

int Projectile::getDamage() const {
    return damage;
}

void Projectile::setDamage(int damage) {
    Projectile::damage = damage;
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
    Projectile::x = x;
}

float Projectile::getY() const {
    return y;
}

void Projectile::setY(float y) {
    Projectile::y = y;
}

const sf::Clock &Projectile::getClock() const {
    return clock;
}

void Projectile::setClock(const sf::Clock &clock) {
    Projectile::clock = clock;
}

const sf::Mouse &Projectile::getMouse() const {
    return mouse;
}

void Projectile::setMouse(const sf::Mouse &mouse) {
    Projectile::mouse = mouse;
}

float Projectile::getVelX() const {
    return velX;
}

void Projectile::setVelX(float velX) {
    Projectile::velX = velX;
}

float Projectile::getVelY() const {
    return velY;
}

void Projectile::setVelY(float velY) {
    Projectile::velY = velY;
}

float Projectile::getDiffX() const {
    return diffX;
}

void Projectile::setDiffX(float diffX) {
    Projectile::diffX = diffX;
}

float Projectile::getDiffY() const {
    return diffY;
}

void Projectile::setDiffY(float diffY) {
    Projectile::diffY = diffY;
}

float Projectile::getMagnitude() const {
    return magnitude;
}

void Projectile::setMagnitude(float magnitude) {
    Projectile::magnitude = magnitude;
}

float Projectile::getRndX() const {
    return rndX;
}

void Projectile::setRndX(float rndX) {
    Projectile::rndX = rndX;
}

float Projectile::getRndY() const {
    return rndY;
}

void Projectile::setRndY(float rndY) {
    Projectile::rndY = rndY;
}

void Projectile::draw(sf::RenderWindow &window) {

}

const sf::RectangleShape &Projectile::getHitbox() const {
    return hitbox;
}

void Projectile::setHitbox(const sf::RectangleShape &hitbox) {
    Projectile::hitbox = hitbox;
}

