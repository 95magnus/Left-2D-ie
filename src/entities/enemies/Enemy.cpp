//
// Created by Eivind Hystad on 30/11/2016.
//

#include "Enemy.h"
//#include "Player.h"

Enemy::Enemy(sf::Vector2f spawnPos) : Entity(spawnPos) {
    // Laster inn texture
    if (!texture.loadFromFile("resources/textures/spritesheets/zombie.png")) {
        printf("Couldn't load zombie texture.");
        sprite.setFillColor(sf::Color::Blue);
    } else {
        sprite.setTexture(&texture);
    }
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
    healthBar.setSize(sf::Vector2f(50,10));
    healthBar.setFillColor(sf::Color::Green);
    healthBar.setOutlineColor(sf::Color::Black);
    healthBar.setOutlineThickness(2);
    healthBar.setPosition(sprite.getPosition().x, sprite.getPosition().y - 30);
    //hpBarBG = healthBar;
    //hpBarBG.setFillColor(sf::Color::Red);
    cycleClock.restart();
    rewardPoints = 10;
    target = sf::Vector2f(0, 0);
}

void Enemy::buff(int percent) {
    percent /= 100;
    damage = damage + damage*percent;
    health = health + health*percent;
    speed = speed + speed*percent;
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
    //target = sf::Vector2f(600, 500);

    // Under får zombien en retning å gå, den vil bevege seg likt som prosjektilene
    diffX = target.x - sprite.getPosition().x;
    diffY = target.y - sprite.getPosition().y;
    magnitude = sqrtf(diffX*diffX + diffY*diffY);
    velX = diffX/magnitude*speed;
    velY = diffY/magnitude*speed;
    //hitbox.setSize(sprite.getSize());

    worldPos.x += velX * deltaTime;
    worldPos.y += velY * deltaTime;

    sprite.setPosition(worldPos);
    hitbox.setPosition(worldPos);

    //sprite.move(velX*deltaTime, velY*deltaTime);
    //hitbox.move(velX*deltaTime, velY*deltaTime);


}

void Enemy::update(std::vector<sf::Vector2f> players, float deltaTime) {
    // Går gjennom lista med spillerenes posisjoner for å finne den nærmeste
    /*for (auto it = players.begin(); it != players.end(); it++) {
        if (abs(target.x - it->x) < target.x && abs(target.y - it->y)) {
            target = *it;
        }
    }
    for (int i = 0; i < players.size(); i++) {
        if (abs(players[i].x - sprite.getPosition().x) < abs(target.x - sprite.getPosition().x)
                && abs(players[i].y - sprite.getPosition().y) < abs(target.y - sprite.getPosition().y)) {
            target = players[i];
        }
    }*/

    //target = sf::Vector2f(600, 500);
    if (worldPos == target)
        return;

    // Under får zombien en retning å gå, den vil bevege seg likt som prosjektilene
    diffX = target.x - sprite.getPosition().x;
    diffY = target.y - sprite.getPosition().y;
    magnitude = sqrtf(diffX*diffX + diffY*diffY);
    velX = diffX/magnitude*speed;
    velY = diffY/magnitude*speed;
    hitbox.setSize(sprite.getSize());
    hitbox.setPosition(sprite.getPosition());
    sprite.move(velX*deltaTime, velY*deltaTime);
    hitbox.move(velX*deltaTime, velY*deltaTime);
    rewardPoints = 10;
}

void Enemy::translate(sf::Vector2f offset) {
    //if (xOffs + offset.x > 0 && xOffs + offset.x < windowSize.x)


    xOffs += offset.x;

    yOffs += offset.y;
}

void Enemy::draw(sf::RenderWindow &window) {
    animationCycler(0.5);
    if (target.x>= sprite.getPosition().x) {
        goingRight = false;
    }
    if (target.x + 10 < sprite.getPosition().x) {
        goingRight = true;
    }
    if (!goingRight) {
        sf::Vector2f xy = sprite.getPosition();
        sprite.setScale(-0.2, 0.2);
        hitbox.setSize(sprite.getSize());
        hitbox.setScale(sprite.getScale());
        hitbox.setPosition(sprite.getPosition());
        //sprite.setPosition(xy);
    }
    if (goingRight){
        sprite.setScale(0.2, 0.2);
        hitbox.setSize(sprite.getSize());
        hitbox.setScale(sprite.getScale());
        hitbox.setPosition(sprite.getPosition());
    }
    //hpBarBG.setPosition(healthBar.getPosition());
    //healthBar.setSize(sf::Vector2f((healthBar.getSize().x - healthBar.getSize().x*((maxHealth - health)/maxHealth)), healthBar.getSize().y));
    sprite.setFillColor(sf::Color(255, hit, hit));
    if (hit < 255) {
        hit += 5;
    }
    window.draw(sprite);
    window.draw(hitbox);
    window.draw(collisionBox);
    //window.draw(hpBarBG);
    //window.draw(healthBar);
}

void Enemy::getHit(int damage) {
    health = health - damage;
    std::cout << std::to_string(health) << std::endl;
    hit = 0;
}

int Enemy::getHealth() const {
    return health;
}

void Enemy::setHealth(int health) {
    Enemy::health = health;
}

void Enemy::setTarget(sf::Vector2f pos) {
    target = pos;
}
