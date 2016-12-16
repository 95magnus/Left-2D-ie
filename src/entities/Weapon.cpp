#include <iostream>
#include "Weapon.h"
#include "../util/ResourceLoader.h"


Weapon::Weapon(sf::RenderWindow &window, int wepStage, float rps, bool spray, int posX, int posY)
        : Entity(sf::Vector2f(posX, posY)), window(window){
    this->rps = rps;
    this->damage = 10;

    sprite.setPosition(posX, posY);
    this->spray = spray;
    reloading = false;
    reloadProgress.setSize(sf::Vector2f(40, 5));
    reloadProgress.setPosition(sprite.getPosition());
    reloadProgress.setFillColor(sf::Color::Yellow);
    reloadProgress.setOutlineColor(sf::Color::Black);
    reloadProgress.setOutlineThickness(1);
    bulletsFired = 0;
    weaponStage = wepStage;

    spriteSide = weaponStageIntRectsSide[wepStage];

    ResourceLoader loader("resources/");

    projectileTexture = &loader.loadTexture("spritesheets/projectiles.png");

    texture = &loader.loadTexture("spritesheets/weapons1.png");
    text[1] = texture;
    text[2] = texture;
    text[3] = texture;
    text[4] = texture;

    texture = &loader.loadTexture("spritesheets/weapons.png");
    text[0] = texture;
    text[5] = texture;

    soundBuffer.loadFromFile("resources/sound_effects/machinegun_loop1.wav");

    sprite.setTexture(texture);
    sprite.setSize(sf::Vector2f(spriteSide.width, spriteSide.height));

    sprite.setOutlineThickness(2);
    sprite.setOutlineColor(sf::Color::Red);
    sound.setBuffer(soundBuffer);
}

Weapon::~Weapon() {
    for (auto &projectile : projectiles)
        delete projectile;
}

void Weapon::update(float deltaTime) {
    for (auto &projectile : projectiles)
        projectile->update(deltaTime);

    //std::cout << weaponStage << std::endl;
    sprite.setTexture(text[weaponStage]);
    sprite.setTextureRect(weaponStageIntRectsSide[weaponStage]);
    sprite.setOrigin(sprite.getLocalBounds().width/2, sprite.getLocalBounds().height/2);
    sprite.setSize(sf::Vector2f(weaponStageIntRectsSide[weaponStage].width,weaponStageIntRectsSide[weaponStage].height));
    for (auto &projectile : projectiles)
        projectile->update(deltaTime);

    if (bulletsFired > magazineSize[weaponStage]) {
        if (!reloading) {
            reloadTimer.restart();
        }
        reloading = true;
        if (reloadTimer.getElapsedTime().asSeconds() >= reloadTime[weaponStage]) {
            bulletsFired = 0;
        }
    } else {
        reloading = false;
    }
    if (reloading) {
        reloadProgress.setPosition(sprite.getPosition().x - reloadProgress.getSize().x/2 + 5, sprite.getPosition().y + 60);
        reloadProgress.setScale((reloadTimer.getElapsedTime().asSeconds()/reloadTime[weaponStage]), 1);
    } else {
        reloadProgress.setPosition(sprite.getPosition().x - reloadProgress.getSize().x/2 + 5, sprite.getPosition().y + 60);
        reloadProgress.setScale(((float)(magazineSize[weaponStage] - bulletsFired)/magazineSize[weaponStage]), 1);
        if (bulletsFired < magazineSize[weaponStage]) {
            reloadProgress.setFillColor(sf::Color::Red);
        }
        if (bulletsFired <= magazineSize[weaponStage]/2) {
            reloadProgress.setFillColor(sf::Color::Yellow);
        }
        if (bulletsFired < magazineSize[weaponStage]/4) {
            reloadProgress.setFillColor(sf::Color::Green);
        }

    }
    for (auto &projectile : projectiles)
        projectile->update(deltaTime);
}

void Weapon::draw(sf::RenderWindow &window) {
    //window.draw(reloadProgress);
    for (auto &proj : projectiles)
        proj->draw(window);

    window.draw(sprite);
}

void Weapon::fire() {
    //if (!reloading) {
        if (clock.getElapsedTime().asSeconds() > 1/rps) {
            projectiles.push_back(new Projectile(window, *projectileTexture, projectileIntRect[weaponStage], 10, 400, spray, angle, sprite.getPosition().x, sprite.getPosition().y));
            clock.restart();
            sound.play();

            bulletsFired++;
            reloading = false;
            reloadTimer.restart();
        }
//    }
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
    this->damage = damage;
}

const sf::RectangleShape &Weapon::getSprite() const {
    return sprite;
}

void Weapon::setSprite(const sf::RectangleShape &sprite) {
    this->sprite = sprite;
}

const sf::IntRect &Weapon::getSpriteFront() const {
    return spriteFront;
}

void Weapon::setSpriteFront(const sf::IntRect &spriteFront) {
    this->spriteFront = spriteFront;
}

const sf::IntRect &Weapon::getSpriteSide() const {
    return spriteSide;
}

void Weapon::setSpriteSide(const sf::IntRect &spriteSide) {
    this->spriteSide = spriteSide;
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
    this->mouse = mouse;
}

const sf::Clock &Weapon::getClock() const {
    return clock;
}

void Weapon::setClock(const sf::Clock &clock) {
    this->clock = clock;
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

bool Weapon::isSpray() const {
    return spray;
}

void Weapon::setSpray(bool spray) {
    Weapon::spray = spray;
}

