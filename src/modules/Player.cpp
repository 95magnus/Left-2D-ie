//
// Created by Eivind Hystad on 14/10/2016.
//

#include "Player.h"
#include "../input/InputManager.h"

// Constructor
Player::Player(sf::RenderWindow* window, InputManager &inputManager) : PlayerController(inputManager) {

    this->window = window;
    health = 100;
    armor = 0;
    kills = 0;
    score = 0;
    money = 0;
    currentDir = Right;
    sprite.setSize(sf::Vector2f(55, 55));
    scaleFactor = 0.25;
    xy = sf::Vector2f(window->getSize().x/2, window->getSize().y/2);
    sprite.setPosition(xy);

    currentWeapon = new Weapon(*window, 0, 6, sprite.getPosition().x - 5, sprite.getPosition().y + 10);

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

    animationDirections.emplace(Up, up);
    animationDirections.emplace(Down, down);
    animationDirections.emplace(Left, left);
    animationDirections.emplace(Right, right);

    hitbox.setOutlineThickness(2);
    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setFillColor(sf::Color(0,0,0,0));

    // Hitboxen blir like brei som karakten, og 1/3 av høyden
    hitbox.setSize(sf::Vector2f(sprite.getSize().x, sprite.getSize().y));
    // Hitboxen ligger rundt karakterens føtter.
    hitbox.setPosition(sprite.getPosition().x, sprite.getPosition().y + 110);

    //shadow.setOrigin(hitbox.getOrigin().x - hitbox.getSize().x/4, hitbox.getOrigin().y - hitbox.getSize().y/4);
    shadow.setRadius(sprite.getSize().x/3);
    shadow.setFillColor(sf::Color(0, 0, 0, 128));
    shadow.setPosition(sprite.getPosition().x, sprite.getPosition().y + 80);
    shadow.setOrigin(shadow.getRadius()/2, shadow.getRadius()/2);

    sprite.setOrigin(sprite.getSize().x/2.2, sprite.getSize().y);
    hitbox.setOrigin(sprite.getOrigin());

    scale(0.8);

    animationCycler(animationDirections[currentDir]);
}

// Destructor
Player::~Player() {

}

void Player::update(float deltaTime) {
    PlayerController::update(deltaTime);

    //sprite.setPosition(xy);

    speedClock.restart();
    currentWeapon->rotateWeapon();
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        currentWeapon->fire();
    }

    auto it = currentWeapon->getBullets().begin();
    while(it != currentWeapon->getBullets().end()) {
        it->update();

        if (it->getClock().getElapsedTime().asSeconds() >= 5) {
            it = currentWeapon->getBullets().erase(it);
        } else {
            ++it;
        }
    }
}


void Player::draw(sf::RenderWindow &window) {

    if (!moving) {
        if (currentDir == Right) {
            sprite.setSize(sf::Vector2f(right[0].width*scaleFactor, right[0].height*scaleFactor));
            sprite.setTextureRect(right[0]);
            sprite.setPosition(xy.x + 15*scaleFactor, xy.y);
        }
        if (currentDir == Left) {
            sprite.setSize(sf::Vector2f(left[0].width*scaleFactor, left[0].height*scaleFactor));
            sprite.setTextureRect(left[0]);
            sprite.setPosition(xy.x + 15*scaleFactor, xy.y);
        }
        if (currentDir == Up) {
            sprite.setSize(sf::Vector2f(up[0].width*scaleFactor, up[0].height*scaleFactor));
            sprite.setTextureRect(up[0]);
            sprite.setPosition(xy.x + 15*scaleFactor, xy.y);
        }
        if (currentDir == Down) {
            sprite.setSize(sf::Vector2f(down[0].width*scaleFactor, down[0].height*scaleFactor));
            sprite.setTextureRect(down[0]);
            sprite.setPosition(xy.x + 15*scaleFactor, xy.y);
        }
    }

    window.draw(shadow);
    window.draw(sprite);
    window.draw(hitbox);

    for (auto it = currentWeapon->getBullets().begin(); it != currentWeapon->getBullets().end(); ++it) {
        window.draw(it->getSprite());
    }
    window.draw(currentWeapon->getSprite());
}

sf::Vector2f Player::move(float deltaTime) {
    if (moveDirection.x != 0 || moveDirection.y != 0) {
        /*
        sprite.move(moveDirection * speed * deltaTime);
        hitbox.move(moveDirection * speed * deltaTime);
        shadow.move(moveDirection * speed * deltaTime);

        xy = sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y);
        currentWeapon->setPosition(xy.x, xy.y);
        */
        if (abs(moveDirection.x) >= abs(moveDirection.y))
            currentDir = (moveDirection.x < 0) ? Left : Right;
        else
            currentDir = (moveDirection.y < 0) ? Up : Down;

        moving = true;
        animationCycler(animationDirections[currentDir]);

        return moveDirection * speed * deltaTime;
    } else {
        moving = false;

        return sf::Vector2f(0, 0);
    }
}

void Player::scale(float x) {
    sprite.setScale(x, x);
    scaleFactor *= x;
    hitbox.setScale(x, x);
    hitbox.move(0, -50*x);

    shadow.setScale(x, x);
    shadow.move(0, -50*x);
}

void Player::animationCycler(std::vector<sf::IntRect> dir) {

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
                sprite.setPosition(xy.x + 12*scaleFactor, xy.y);
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
                sprite.setSize(sf::Vector2f(dir[3].width*scaleFactor, dir[3].height*scaleFactor));
                sprite.setTextureRect(dir[3]);
                sprite.setPosition(xy.x + 3, xy.y);
            }
            if (clock.getElapsedTime().asSeconds() < 0.4) {
                sprite.setSize(sf::Vector2f(dir[1].width*scaleFactor, dir[1].height*scaleFactor));
                sprite.setTextureRect(dir[1]);
                sprite.setPosition(xy.x + 3, xy.y);
            }
            if (clock.getElapsedTime().asSeconds() < 0.2) {
                sprite.setSize(sf::Vector2f(dir[4].width*scaleFactor, dir[1].height*scaleFactor));
                sprite.setTextureRect(dir[4]);
                sprite.setPosition(xy.x + 3, xy.y);

            }
        }

    } if (!moving) {
        sprite.setSize(sf::Vector2f(dir[0].width*scaleFactor, dir[0].height*scaleFactor));
        sprite.setTextureRect(dir[0]);
        sprite.setPosition(xy.x + 15*scaleFactor, xy.y);
    }

}

void Player::mousePressed(int x, int y, sf::Mouse::Button button) {

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

    // Kaller destruktøren for player
    delete this;
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

Player::Direction Player::getCurrentDir() const {
    return currentDir;
}

void Player::setCurrentDir(Player::Direction currentDir) {
    Player::currentDir = currentDir;
}

std::vector<Projectile> *Player::getBullets() {
    return &currentWeapon->getBullets();
}