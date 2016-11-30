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
    currentDir = Left;
    sprite.setSize(sf::Vector2f(55, 55));
    scaleFactor = 0.25;

    texture.setSmooth(false);
    texture.setRepeated(false);

    //texture.setSrgb(false);

    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(1);

    //Load Texture
    if (!texture.loadFromFile("resources/textures/spritesheets/player.png")) {
        // Spilleren blir blå hvis bildet ikke blir lastet
        sprite.setFillColor(sf::Color::Green);
    } else {
        sprite.setTexture(&texture);
    }



    hitbox.setOutlineThickness(2);
    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setFillColor(sf::Color(0,0,0,0));

    // Hitboxen blir like brei som karakten, og 1/3 av høyden
    hitbox.setSize(sf::Vector2f(sprite.getSize().x, sprite.getSize().y));
    // Hitboxen ligger rundt karakterens føtter.
    hitbox.setPosition(sprite.getPosition().x, sprite.getPosition().y + 110);

    scale(0.8);
}

// Deconstructor
Player::~Player() {

}

// Action functions
void Player::moveUp(float dt) {
    sprite.move(0.f, speed * dt * -1);
    hitbox.move(0.f, speed * dt * -1);
    xy = sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y);
}

void Player::moveDown(float dt) {
    sprite.move(0.f, speed * dt);
    hitbox.move(0.f, speed * dt);
    xy = sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y);
}

void Player::moveRight(float dt) {
    sprite.move(speed * dt, 0.f);
    hitbox.move(speed * dt, 0.f);
    xy = sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y);
}

void Player::moveLeft(float dt) {
    sprite.move(speed * dt * -1, 0.f);
    hitbox.move(speed * dt * -1, 0.f);
    xy = sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y);
}

void Player::draw(sf::RenderWindow &window) {
    moving = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        moveDown(0.004);
        moving = true;
        currentDir = Down;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        moveUp(0.004);
        moving = true;
        currentDir = Up;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        moveLeft(0.004);
        moving = true;
        currentDir = Left;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        moveRight(0.004);
        moving = true;
        currentDir = Right;
    }

    if (currentDir == Up) {
        animationCycler(up);
    }
    if (currentDir == Down) {
        animationCycler(down);
    }
    if (currentDir == Left) {
        animationCycler(left);
    }
    if (currentDir == Right) {
        animationCycler(right);
    }

    window.draw(sprite);
    window.draw(hitbox);
    sprite.setPosition(xy);
}

void Player::scale(float x) {
    sprite.setScale(x, x);
    scaleFactor *= x;
    hitbox.setScale(x, x);
    hitbox.move(0, -50*x);
}

void Player::animationCycler(sf::IntRect dir[5]) {

    /* -- ¡IMPORTANT! --
     * I wrote this function to cycle through the animation frames
     * there were some issues when cycling.
     *
     * The textures would warp and some would be larger than intended or distorted.
     * So I came up with a shady solution.
     *
     * You may try to alter the size of the model, but you have to increase the non-relative numbers below aswell,
     * or there will be issues. It's best just not to alter anything.
     *
     * I've learned from my mistakes and the same thing can't happen to the enemies,
     * since the frames doesnt differ in dimentions
     *
     * Forgive me.
     * - EH
     * */

    // this function has brought shame upon my ancestors
    /*
     * for (int e = 0; e <= 100; e++) {
     *      printf("sorry for this!");
     * }
     * */

    if (moving) {
        if (currentDir == Left) {
            if (clock.getElapsedTime().asSeconds() >= 0.8*0.66) {
                clock.restart();
            }
            if (clock.getElapsedTime().asSeconds() < 0.8*0.66) {
                sprite.setSize(sf::Vector2f(dir[2].width*scaleFactor, dir[2].height*scaleFactor));
                sprite.setTextureRect(dir[2]);
            }
            if (clock.getElapsedTime().asSeconds() < 0.6*0.66) {
                sprite.setSize(sf::Vector2f(dir[3].width*scaleFactor, dir[3].height*scaleFactor));
                sprite.setTextureRect(dir[3]);
                sprite.setPosition(xy.x - 75*scaleFactor, xy.y);
            }
            if (clock.getElapsedTime().asSeconds() < 0.4*0.66) {
                sprite.setSize(sf::Vector2f(dir[4].width*scaleFactor, dir[4].height*scaleFactor));
                sprite.setTextureRect(dir[4]);
                sprite.setPosition(xy.x - 75*scaleFactor, xy.y);
            }
            if (clock.getElapsedTime().asSeconds() < 0.2*0.66) {
                sprite.setSize(sf::Vector2f(dir[1].width*scaleFactor, dir[1].height*scaleFactor));
                sprite.setTextureRect(dir[1]);
                sprite.setPosition(xy.x - 75*scaleFactor, xy.y);

            }
        }
        if (currentDir == Right) {
            if (clock.getElapsedTime().asSeconds() >= 0.8*0.66) {
                clock.restart();
            }
            if (clock.getElapsedTime().asSeconds() < 0.8*0.66) {
                sprite.setSize(sf::Vector2f(dir[2].width*scaleFactor, dir[2].height*scaleFactor));
                sprite.setTextureRect(dir[2]);
                sprite.setPosition(xy.x + 15*scaleFactor - 17, xy.y);
            }
            if (clock.getElapsedTime().asSeconds() < 0.6*0.66) {
                sprite.setSize(sf::Vector2f(dir[3].width*scaleFactor, dir[3].height*scaleFactor));
                sprite.setTextureRect(dir[3]);
                sprite.setPosition(xy.x - 75*scaleFactor - 17, xy.y);
            }
            if (clock.getElapsedTime().asSeconds() < 0.4*0.66) {
                sprite.setSize(sf::Vector2f(dir[4].width*scaleFactor, dir[4].height*scaleFactor));
                sprite.setTextureRect(dir[4]);
                sprite.setPosition(xy.x - 75*scaleFactor - 17, xy.y);
            }
            if (clock.getElapsedTime().asSeconds() < 0.2*0.66) {
                sprite.setSize(sf::Vector2f(dir[1].width*scaleFactor, dir[1].height*scaleFactor));
                sprite.setTextureRect(dir[1]);
                sprite.setPosition(xy.x - 75*scaleFactor - 17, xy.y);

            }
        }
        if (currentDir == Down) {
            if (clock.getElapsedTime().asSeconds() >= 0.8) {
                clock.restart();
            }
            if (clock.getElapsedTime().asSeconds() < 0.8) {
                sprite.setSize(sf::Vector2f(dir[2].width*scaleFactor, dir[2].height*scaleFactor));
                sprite.setTextureRect(dir[2]);
                sprite.setPosition(xy.x + 3, xy.y);
            }
            if (clock.getElapsedTime().asSeconds() < 0.6) {
                sprite.setSize(sf::Vector2f(dir[4].width*scaleFactor, dir[4].height*scaleFactor));
                sprite.setTextureRect(dir[4]);
                sprite.setPosition(xy.x + 3, xy.y);
            }
            if (clock.getElapsedTime().asSeconds() < 0.4) {
                sprite.setSize(sf::Vector2f(dir[3].width*scaleFactor, dir[3].height*scaleFactor));
                sprite.setTextureRect(dir[3]);
                sprite.setPosition(xy.x + 3, xy.y);
            }
            if (clock.getElapsedTime().asSeconds() < 0.2) {
                sprite.setSize(sf::Vector2f(dir[1].width*scaleFactor, dir[1].height*scaleFactor));
                sprite.setTextureRect(dir[1]);
                sprite.setPosition(xy.x + 3, xy.y);

            }
        }
        if (currentDir == Up) {
            if (clock.getElapsedTime().asSeconds() >= 0.8) {
                clock.restart();
            }
            if (clock.getElapsedTime().asSeconds() < 0.8) {
                sprite.setSize(sf::Vector2f(dir[2].width*scaleFactor, dir[2].height*scaleFactor));
                sprite.setTextureRect(dir[2]);
                sprite.setPosition(xy.x + 3, xy.y);
            }
            if (clock.getElapsedTime().asSeconds() < 0.6) {
                sprite.setSize(sf::Vector2f(dir[4].width*scaleFactor, dir[4].height*scaleFactor));
                sprite.setTextureRect(dir[4]);
                sprite.setPosition(xy.x + 3, xy.y);
            }
            if (clock.getElapsedTime().asSeconds() < 0.4) {
                sprite.setSize(sf::Vector2f(dir[3].width*scaleFactor, dir[3].height*scaleFactor));
                sprite.setTextureRect(dir[3]);
                sprite.setPosition(xy.x + 3, xy.y);
            }
            if (clock.getElapsedTime().asSeconds() < 0.2) {
                sprite.setSize(sf::Vector2f(dir[1].width*scaleFactor, dir[1].height*scaleFactor));
                sprite.setTextureRect(dir[1]);
                sprite.setPosition(xy.x + 3, xy.y);

            }
        }

    } else {
        sprite.setSize(sf::Vector2f(dir[0].width*scaleFactor, dir[0].height*scaleFactor));
        sprite.setTextureRect(dir[0]);
        sprite.setPosition(xy.x + 15*scaleFactor, xy.y);
    }

}

void Player::hit() {
    //sounds effects on hit.
    SBuffer.loadFromFile("damage_hit1.wav");
    sound.setBuffer(SBuffer);
    sound.play();
    //
    Player::setHealth(Player::getHealth() - 10);
}

void Player::death() {
    SBuffer.loadFromFile("wilhelm_scream.wav");
    sound.setBuffer(SBuffer);
    sound.play();
    // TODO: Legge til dødsanimasjon når health = 0?
    // TODO: (kanskje player faller i bakken og blinker i 3 sek så forsvinner den slik som på gamle spill)

    // Kaller dekonstruktøren for player
    //delete this;
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
