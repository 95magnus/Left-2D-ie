#include "Enemy.h"

Enemy::Enemy(sf::Vector2f spawnPos) : Entity(spawnPos) {
    // Laster inn texture
    if (!texture.loadFromFile("resources/textures/spritesheets/zombie.png")) {
        printf("Couldn't load zombie texture.");
        sprite.setFillColor(sf::Color::Blue);
    } else {
        sprite.setTexture(&texture);
    }
    scoreReward = 20;
    goingRight = false;
    health = 100;
    maxHealth = 100;
    damage = 20;
    speed = 50;
    hit = 0;
    sprite.setPosition(spawnPos.x, spawnPos.y);
    sprite.setSize(sf::Vector2f(100, 100));
    //hitbox.setSize(sf::Vector2f(40, 40));
    hitbox.setFillColor(sf::Color(255, 255, 255, 00));
    //hitbox.setPosition(sprite.getPosition().x - hitbox.getSize().x*1.5, sprite.getPosition().y + hitbox.getSize().y*1.9);
    hitbox.setOutlineColor(sf::Color::Blue);
    hitbox.setOutlineThickness(3);
    sprite.setOrigin(sprite.getSize().x, sprite.getSize().y/ 2);
    sprite.setOrigin(sprite.getOrigin().x + sprite.getOrigin().x, sprite.getOrigin().y);
    hitbox.setOrigin(sprite.getOrigin());
    healthBar.setSize(sf::Vector2f(50,5));
    healthBar.setFillColor(sf::Color::Green);
    healthBar.setOutlineColor(sf::Color::Black);
    healthBar.setOutlineThickness(1);
    healthBar.setPosition(sprite.getPosition().x, sprite.getPosition().y);
    hpBarBG = healthBar;
    hpBarBG.setFillColor(sf::Color::Red);
    cycleClock.restart();
    target = sf::Vector2i(-1, -1);
}

void Enemy::buff(int percent) {
    percent /= 100;
    damage = damage + damage*percent;
    health = health + health*percent;
    speed = speed + speed*percent;
    scoreReward = scoreReward + scoreReward*percent;
}

void Enemy::dealDamage(Player *player) {
    if (attackTimer.getElapsedTime().asSeconds() > 1) {
        player->setHealth(player->getHealth() - damage);
        player->hit();
        attackTimer.restart();
    }
}

void Enemy::animationCycler(float interval) {
    if (cycleClock.getElapsedTime().asSeconds() >= 1) {
        cycleClock.restart();
    }
    if (cycleClock.getElapsedTime().asSeconds() < 0.5) {
        sprite.setSize(sf::Vector2f(rect[2].width, rect[2].height));
        sprite.setTextureRect(rect[2]);
    } else {
        sprite.setSize(sf::Vector2f(rect[1].width, rect[1].height));
        sprite.setTextureRect(rect[1]);
    }
}

Enemy::~Enemy() {
}

void Enemy::update(float deltaTime) {
    if (target == sf::Vector2i(worldPos.x, worldPos.y)) {
        requestNewTarget = true;
        return;
    }

    sf::Vector2f direction;
    direction.x = target.x - worldPos.x;
    direction.y = target.y - worldPos.y;

    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    direction /= length;

    if (requestNewTarget)
        direction = sf::Vector2f(0, 0);

    worldPos += direction * (speed * deltaTime);

    sprite.setPosition(worldPos);
    hitbox.setPosition(worldPos);

    goingRight = direction.x > 0;
    moving = direction != sf::Vector2f(0, 0);

    if (moving)
        animationCycler(0.5);
}

void Enemy::update(std::vector<sf::Vector2f> players, float deltaTime) {

    // Under får zombien en retning å gå, den vil bevege seg likt som prosjektilene
    diffX = target.x - sprite.getPosition().x;
    diffY = target.y - sprite.getPosition().y;
    magnitude = sqrt(diffX*diffX + diffY*diffY);
    velX = diffX/magnitude*speed;
    velY = diffY/magnitude*speed;

    worldPos.x += velX * deltaTime;
    worldPos.y += velY * deltaTime;

    hitbox.setSize(sprite.getSize());
    hitbox.setPosition(worldPos);
    sprite.setPosition(worldPos);
}

void Enemy::draw(sf::RenderWindow &window) {
    if (goingRight) {
        sprite.setScale(-0.2, 0.2);
        hitbox.setSize(sprite.getSize());
        hitbox.setScale(sprite.getScale());
    } else {
        sprite.setScale(0.2, 0.2);
        hitbox.setSize(sprite.getSize());
        hitbox.setScale(sprite.getScale());
    }
    healthBar.setPosition(sprite.getPosition().x - healthBar.getLocalBounds().width/2, sprite.getPosition().y - 20);
    hpBarBG.setPosition(healthBar.getPosition());
    healthBar.setScale(((float)health/maxHealth), 1);
    sprite.setFillColor(sf::Color(255, hit, hit));
    if (hit < 255) {
        hit += 5;
    }
    window.draw(sprite);
    //window.draw(hitbox);
    window.draw(collisionBox);
    window.draw(hpBarBG);
    window.draw(healthBar);
}

void Enemy::getHit(int damage) {
    health = health - damage;
    //std::cout << std::to_string(health) << std::endl;
    hit = 0;
}

int Enemy::getHealth() const {
    return health;
}

void Enemy::setHealth(int health) {
    Enemy::health = health;
}

void Enemy::setTarget(sf::Vector2i pos) {
    target = pos;
    requestNewTarget = false;
}

int Enemy::getScoreReward() const {
    return scoreReward;
}

void Enemy::setScoreReward(int scoreReward) {
    Enemy::scoreReward = scoreReward;
}
