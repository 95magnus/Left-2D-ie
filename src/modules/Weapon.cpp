//
// Created by Eivind Hystad on 20/11/2016.
//

#include "Weapon.h"

Weapon::Weapon(int wepStage, float rps, int posX, int posY) {
    sprite.setPosition(posX, posY);
    weaponStage = wepStage;
    this->rps = rps;
    spriteFront = weaponStageIntRectsFront[wepStage];
    spriteSide = weaponStageIntRectsSide[wepStage];
    if (!texture.loadFromFile("resources/textures/spritesheets/weapons.png")) {
        // Spilleren blir blå hvis bildet ikke blir lastet
        sprite.setFillColor(sf::Color::Green);
    } else {
        sprite.setTexture(&texture);
    }
    if (!projectileTexture.loadFromFile("resources/textures/spritesheets/projectiles.png")) {

    }
    if (soundBuffer.loadFromFile("resources/sound_effects/machinegun_loop1.wav")) {

    }
    sprite.setSize(sf::Vector2f(spriteSide.width, spriteSide.height));
    sprite.setTextureRect(spriteSide);
    sprite.setOrigin(sprite.getSize().x/2, sprite.getOrigin().y/2);
    sprite.scale(0.2, 0.2);
    sound.setBuffer(soundBuffer);
}

Weapon::~Weapon() {

}

void Weapon::fire() {
    if (clock.getElapsedTime().asSeconds() > 1/rps) {
        Projectile bullet(projectileTexture, projectileIntRect[weaponStage], 100, angle, this->sprite.getPosition().x, this->sprite.getPosition().y);
        bullets.push_back(bullet);
        clock.restart();
        sound.play();
    }
}

void Weapon::rotateWeapon() {
    angle = (float) (atan2(sprite.getPosition().y - mouse.getPosition().y, sprite.getPosition().x - mouse.getPosition().x)*180/3.1416);
    sprite.setRotation(angle);
    if (mouse.getPosition().x > sprite.getPosition().x) {
        flipRight();
    } else {
        flipLeft();
    }
}

void Weapon::flipLeft() {
    sprite.setScale(0.2, 0.2);
}

void Weapon::flipRight() {
    sprite.setScale(0.2, -0.2);
}

void Weapon::setPosition(int x, int y) {
    sprite.setPosition(x, y);
}

std::vector<Projectile> &Weapon::getBullets() {
    return bullets;
}

int Weapon::getDamage() const {
    return damage;
}

void Weapon::setDamage(int damage) {
    Weapon::damage = damage;
}

const sf::RectangleShape &Weapon::getSprite() const {
    return sprite;
}

void Weapon::setSprite(const sf::RectangleShape &sprite) {
    Weapon::sprite = sprite;
}

const sf::IntRect &Weapon::getSpriteFront() const {
    return spriteFront;
}

void Weapon::setSpriteFront(const sf::IntRect &spriteFront) {
    Weapon::spriteFront = spriteFront;
}

const sf::IntRect &Weapon::getSpriteSide() const {
    return spriteSide;
}

void Weapon::setSpriteSide(const sf::IntRect &spriteSide) {
    Weapon::spriteSide = spriteSide;
}

const sf::Texture &Weapon::getTexture() const {
    return texture;
}

void Weapon::setTexture(const sf::Texture &texture) {
    Weapon::texture = texture;
}

const sf::Texture &Weapon::getProjectileTexture() const {
    return projectileTexture;
}

void Weapon::setProjectileTexture(const sf::Texture &projectileTexture) {
    Weapon::projectileTexture = projectileTexture;
}

const sf::Mouse &Weapon::getMouse() const {
    return mouse;
}

void Weapon::setMouse(const sf::Mouse &mouse) {
    Weapon::mouse = mouse;
}

const sf::Clock &Weapon::getClock() const {
    return clock;
}

void Weapon::setClock(const sf::Clock &clock) {
    Weapon::clock = clock;
}

float Weapon::getRps() const {
    return rps;
}

void Weapon::setRps(float rps) {
    Weapon::rps = rps;
}

const sf::IntRect *Weapon::getWeaponStageIntRectsSide() const {
    return weaponStageIntRectsSide;
}

const sf::IntRect *Weapon::getWeaponStageIntRectsFront() const {
    return weaponStageIntRectsFront;
}

const sf::IntRect *Weapon::getProjectileIntRect() const {
    return projectileIntRect;
}

void Weapon::setBullets(const std::vector<Projectile> &bullets) {
    Weapon::bullets = bullets;
}

float Weapon::getAngle() const {
    return angle;
}

void Weapon::setAngle(float angle) {
    Weapon::angle = angle;
}

int Weapon::getWeaponStage() const {
    return weaponStage;
}

void Weapon::setWeaponStage(int weaponStage) {
    Weapon::weaponStage = weaponStage;
}

