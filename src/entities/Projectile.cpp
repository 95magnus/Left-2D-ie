#include "Projectile.h"

Projectile::Projectile(sf::RenderWindow &window, sf::Texture &texture, sf::IntRect rect, int damage, int speed, bool spray, float angle, float x, float y)
        : Entity(sf::Vector2f(x, y)) {
    sprite.setTexture(&texture);
    sprite.setTextureRect(rect);
    sprite.setSize(sf::Vector2f(rect.width, rect.height));
    sprite.setRotation(angle);
    this->damage = damage;

    speed = 450;
    sprite.setPosition(worldPos);

    this->speed = speed;
    this->spray = spray;

    sprite.setScale(0.1, 0.1);

    velX = -cos(angle * 3.1416/180) * speed;
    velY = -sin(angle * 3.1416/180) * speed;

    rndX = fRand();
    rndY = fRand();

    sprite.setOutlineColor(sf::Color::Cyan);
    sprite.setOutlineThickness(2);
}

Projectile::~Projectile() {

}

float Projectile::fRand() {
    if (!spray) {
        return 1;
    }
    float rnd = (float) (rand() % -100 + 100);
    return rnd / 100.0f;
}

void Projectile::update(float deltaTime) {
    sf::Vector2f vel(velX * rndX, velY * rndY);
    float length = sqrt(vel.x * vel.x + vel.y * vel.y);
    vel /= length;

    worldPos.x += vel.x * speed * deltaTime;
    worldPos.y += vel.y * speed * deltaTime;

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
