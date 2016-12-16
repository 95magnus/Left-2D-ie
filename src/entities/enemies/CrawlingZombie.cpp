//
// Created by Eivind Hystad on 13/12/2016.
//

#include "CrawlingZombie.h"

CrawlingZombie::CrawlingZombie(const sf::Vector2f &spawnPos) : Enemy(spawnPos) {
    if (!texture.loadFromFile("resources/textures/spritesheets/crawling_zombie.png")) {
        printf("Couldn't load zombie texture.");
        sprite.setFillColor(sf::Color::Blue);
    } else {
        sprite.setTexture(&texture);
    }
    rect[0] = sf::IntRect(0, 0, 285, 195);
    rect[1] = sf::IntRect(0, 0, 285, 195);
    rect[2] = sf::IntRect(0, 196, 270 ,195);
    speed /= 2;
    damage /= 2;
    hanging = false;
    healthBar.setSize(sf::Vector2f(50,5));
    healthBar.setFillColor(sf::Color::Green);
    healthBar.setOutlineColor(sf::Color::Black);
    healthBar.setOutlineThickness(1);
    healthBar.setPosition(sprite.getPosition().x, sprite.getPosition().y);
    hpBarBG = healthBar;
    hpBarBG.setFillColor(sf::Color::Red);
}

void CrawlingZombie::dealDamage(Player *player) {
    if (hanging == true) {
        if (attackTimer.getElapsedTime().asSeconds() > 1) {
            player->setHealth(player->getHealth() - damage);
            player->hit();
            player->setSpeed(player->getSpeed()/1.8);
            attackTimer.restart();
        }
    }
}

void CrawlingZombie::update(float deltaTime) {
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

    if (abs(diffY) < 5 and abs(diffX) < 5) {
        sprite.setPosition(target.x, target.y);
        hitbox.setPosition(sprite.getPosition());
        if (!hanging) {
            sprite.rotate(-90);
            hanging = true;
        }
    }

    if (abs(diffY) < 90 and abs(diffX) < 90) {
        speed = 450;
    }

}

void CrawlingZombie::draw(sf::RenderWindow &window) {
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
    healthBar.setPosition(sprite.getPosition().x - healthBar.getLocalBounds().width/2, sprite.getPosition().y - 20);
    hpBarBG.setPosition(healthBar.getPosition());
    healthBar.setScale(((float)health/maxHealth), 1);
    sprite.setFillColor(sf::Color(255, hit, hit));
    if (hit < 255) {
        hit += 5;
    }

    if (hanging) {
        sprite.setPosition(sprite.getPosition().x - 40, sprite.getPosition().y + 30);
    }

    window.draw(sprite);
    window.draw(hitbox);
    window.draw(collisionBox);
    window.draw(hpBarBG);
    window.draw(healthBar);

    if (hanging) {
        sprite.setPosition(sprite.getPosition().x + 40, sprite.getPosition().y - 30);
    }

}