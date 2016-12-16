//
// Created by Eivind Hystad on 20/11/2016.
//

#include "Weapon.h"
#include "../util/ResourceLoader.h"

Weapon::Weapon(sf::RenderWindow &window, int wepStage, float rps, int posX, int posY)
        : Entity(sf::Vector2f(posX, posY)), window(window){
    this->rps = rps;
    this->damage = damage;

    sprite.setPosition(posX, posY);
    weaponStage = wepStage;
    spriteFront = weaponStageIntRectsFront[wepStage];
    spriteSide = weaponStageIntRectsSide[wepStage];

    ResourceLoader loader("resources/");

    texture = &loader.loadTexture("spritesheets/weapons.png");
    projectileTexture = &loader.loadTexture("spritesheets/projectiles.png");

    soundBuffer.loadFromFile("resources/sound_effects/machinegun_loop1.wav");

    sprite.setTexture(texture);
    sprite.setSize(sf::Vector2f(spriteSide.width, spriteSide.height));
    sprite.setTextureRect(spriteSide);
    sprite.scale(0.2, 0.2);
    sprite.setOrigin(sprite.getSize().x/2, sprite.getSize().y/2);
    sprite.setOutlineThickness(2);
    sprite.setOutlineColor(sf::Color::Red);
    sound.setBuffer(soundBuffer);

    projectiles.push_back(new Projectile(window, *projectileTexture, projectileIntRect[weaponStage], 10, angle, sprite.getPosition().x, sprite.getPosition().y));
}

Weapon::~Weapon() {
    for (auto &projectile : projectiles)
        delete projectile;
}

void Weapon::update(float deltaTime) {
    for (auto &projectile : projectiles)
        projectile->update(deltaTime);
}

void Weapon::draw(sf::RenderWindow &window) {
    for (auto &projectile : projectiles)
        projectile->draw(window);

    window.draw(sprite);
}

void Weapon::fire() {
    if (clock.getElapsedTime().asSeconds() > 1/rps) {
        projectiles.push_back(new Projectile(window, *projectileTexture, projectileIntRect[weaponStage], 10, angle, sprite.getPosition().x, sprite.getPosition().y));
        clock.restart();
        sound.play();
    }
}

void Weapon::rotateWeapon(int mouseWorldPosX, int mouseWorldPosY) {
    angle = (float) (atan2(sprite.getPosition().y - mouseWorldPosY, sprite.getPosition().x - mouseWorldPosX)*180/3.1416);

    sprite.setRotation(angle);
    if (mouseWorldPosX > sprite.getPosition().x) {
        flipRight();
    } else {
        flipLeft();
    }
}

void Weapon::rotateWeapon(sf::Vector2f direction) {
    angle = (float) ((atan2(-direction.y, -direction.x) * 180) / 3.1416);

    sprite.setRotation(angle);
    if (abs(angle) > 90.0f) {
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

std::vector<Projectile*>& Weapon::getProjectiles() {
    return projectiles;
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
    return *texture;
}

void Weapon::setTexture(sf::Texture* texture) {
    this->texture = texture;
}

const sf::Texture &Weapon::getProjectileTexture() const {
    return *projectileTexture;
}

void Weapon::setProjectileTexture(sf::Texture* projectileTexture) {
    this->projectileTexture = projectileTexture;
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
    this->rps = rps;
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

void Weapon::setProjectiles(const std::vector<Projectile*> bullets) {
    this->projectiles = projectiles;
}

float Weapon::getAngle() const {
    return angle;
}

void Weapon::setAngle(float angle) {
    this->angle = angle;
}

int Weapon::getWeaponStage() const {
    return weaponStage;
}

void Weapon::setWeaponStage(int weaponStage) {
    this->weaponStage = weaponStage;
}

