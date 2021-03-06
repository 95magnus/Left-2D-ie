//
// Created by Eivind Hystad on 14/10/2016.
//

#include "Player.h"
#include "../input/InputManager.h"

Player::Player(sf::RenderWindow &window, sf::View &view, InputManager &inputManager, sf::Vector2f pos)
        : Entity(pos), PlayerController(inputManager, 0), window(window), view(view){
    maxHealth = 100;
    health = maxHealth;
    armor = 0;
    kills = 0;
    score = 0;
    money = 0;
    currentDir = Right;
    sprite.setSize(sf::Vector2f(55, 55));
    scaleFactor = 0.25;
    xy = sf::Vector2f(worldPos.x, worldPos.y - 50);
    sprite.setPosition(xy);

    currentWeapon = new Weapon(window, 0, 5, true, (int) sprite.getPosition().x - 5, (int) sprite.getPosition().y + 10);

    texture.setSmooth(false);
    texture.setRepeated(false);

    //Load Texture
    if (!texture.loadFromFile("resources/textures/spritesheets/player.png")) {
        // Spilleren blir grønn hvis bildet ikke blir lastet
        sprite.setFillColor(sf::Color::Green);
    } else {
        sprite.setTexture(&texture);
    }
    if (!graveStone.loadFromFile("resources/textures/spritesheets/gravestone.png")) {
    }

    hitColor = 255;

    animationDirections.emplace(Up, up);
    animationDirections.emplace(Down, down);
    animationDirections.emplace(Left, left);
    animationDirections.emplace(Right, right);

    hitbox.setOutlineThickness(2);
    hitbox.setOutlineColor(sf::Color::Red);

    hitbox.setFillColor(sf::Color(0,0,0,0));
    // Hitboxen blir like brei som karakten, og 1/3 av høyden
    //hitbox.setSize(sf::Vector2f(sprite.getSize().x, sprite.getSize().y));

    hitbox.setSize(sf::Vector2f(32, 32));
    hitbox.setOrigin(hitbox.getSize().x/2, hitbox.getSize().y/2);

    // Hitboxen ligger rundt karakterens føtter.
    hitbox.setPosition(sprite.getPosition().x, sprite.getPosition().y + 130);

    //shadow.setOrigin(hitbox.getOrigin().x - hitbox.getSize().x/4, hitbox.getOrigin().y - hitbox.getSize().y/4);
    shadow.setRadius(sprite.getSize().x/3);
    shadow.setFillColor(sf::Color(0, 0, 0, 64));
    shadow.setPosition(sprite.getPosition().x, sprite.getPosition().y + 80);
    shadow.setOrigin(shadow.getRadius()/2, shadow.getRadius()/2);

    sprite.setOrigin(sprite.getSize().x/2.2f, sprite.getSize().y);
    //hitbox.setOrigin(sprite.getOrigin().x, sprite.getOrigin().y);

    //sprite.setOutlineThickness(2);
    //sprite.setOutlineColor(sf::Color(0, 255, 0));

    collisionBox = hitbox.getGlobalBounds();

    scale(0.8);

    animationCycler(animationDirections[currentDir]);


    hitBuffer.loadFromFile("resources/sound_effects/damage_hit1.wav");
    hitSound.setBuffer(hitBuffer);

    diedBuffer.loadFromFile("resources/sound_effects/wilhelm_scream.wav");
    deathSound.setBuffer(diedBuffer);

    usingController = sf::Joystick::isConnected(0);
}

Player::~Player() {

}

void Player::update(float deltaTime) {
    PlayerController::update(deltaTime);

    currentWeapon->update(deltaTime);

    speedClock.restart();
    auto mousePos = sf::Mouse::getPosition(window);
    auto mouseWorld = window.mapPixelToCoords(mousePos, view);

    if (usingController) {
        if (viewingDirection == sf::Vector2f(0, 0) && currentDir == Left) {
            sf::Vector2f temp(viewingDirection.x * -1, viewingDirection.y);
            currentWeapon->rotateWeapon(temp);
        } else
            currentWeapon->rotateWeapon(viewingDirection);
    } else {
        currentWeapon->rotateWeapon(mouseWorld.x, mouseWorld.y);
    }

    hitbox.setPosition(worldPos.x, worldPos.y);

    shadow.setPosition(xy.x - 5, xy.y + 50);
    currentWeapon->setPosition(xy.x - 5, xy.y + 10);

    if (usingController) {
        if (shooting && window.hasFocus())
            currentWeapon->fire();
    } else {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && window.hasFocus())
            currentWeapon->fire();
    }

    auto proj = &currentWeapon->getProjectiles();
    for (int i = 0; i < proj->size(); i++) {
        if (proj->at(i)->getClock().getElapsedTime().asSeconds() >= 5) {
            proj->erase(proj->begin() + i);
        }
    }

    collisionBox = hitbox.getGlobalBounds();

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

    sprite.setFillColor(sf::Color(255, hitColor, hitColor));
    if (hitColor < 255) {
        hitColor += 1;
    }

    if (health <= 0) {
        sprite.setScale(0.2, 0.2);
        sprite.setSize(sf::Vector2f(graveStone.getSize().x, graveStone.getSize().y));
        sprite.setTexture(&graveStone);
        sprite.setTextureRect(sf::IntRect(0, 0, graveStone.getSize().x, graveStone.getSize().y));
        sprite.setPosition(sprite.getPosition().x - 25, sprite.getPosition().y + 25);
    }

    window.draw(shadow);
    window.draw(hitbox);

    if (currentDir == Up) {

        currentWeapon->draw(window);

        window.draw(sprite);
    } else {
        window.draw(sprite);

        currentWeapon->draw(window);
    }
}

sf::Vector2f Player::move(float deltaTime) {
    if (moveDirection.x != 0 || moveDirection.y != 0) {
        if (abs(moveDirection.x) >= abs(moveDirection.y))
            currentDir = (moveDirection.x < 0) ? Left : Right;
        else
            currentDir = (moveDirection.y < 0) ? Up : Down;

        moving = true;
        animationCycler(animationDirections[currentDir]);

        worldPos += moveDirection * speed * deltaTime;
        xy = sf::Vector2f(worldPos.x, worldPos.y - 50);

        return moveDirection * speed * deltaTime;
    } else {
        moving = false;

        return sf::Vector2f();
    }
}

void Player::scale(float x) {
    sprite.setScale(x, x);
    scaleFactor *= x;

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
     * since the frames doesnt differ in dimenions
     *
     * This function has brought shame upon my ancestors
     * Forgive me.
     * - EH
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

    }
    if (!moving) {
        sprite.setSize(sf::Vector2f(dir[0].width*scaleFactor, dir[0].height*scaleFactor));
        sprite.setTextureRect(dir[0]);
        sprite.setPosition(xy.x + 15*scaleFactor, xy.y);
    }
}

void Player::hit() {
    hitSound.play();
    hitColor = 0;
}

void Player::onDeath() {
    deathSound.play();
}

int Player::getHealth() const {
    return health;
}

void Player::setHealth(int health) {
    this->health = health;
}

int Player::getSpeed() const {
    return speed;
}

void Player::setSpeed(int speed) {
    this->speed = speed;
}

int Player::getScore() const {
    return score;
}

void Player::setScore(int score) {
    this->score = score;
}

int Player::getMoney() const {
    return money;
}

void Player::setMoney(int money) {
    this->money = money;
}

int Player::getArmor() const {
    return armor;
}

void Player::setArmor(int armor) {
    this->armor = armor;
}

int Player::getKills() const {
    return kills;
}

void Player::setKills(int kills) {
    this->kills = kills;
}

Player::Direction Player::getCurrentDir() const {
    return currentDir;
}

void Player::setCurrentDir(Player::Direction currentDir) {
    this->currentDir = currentDir;
}

std::vector<Projectile*>& Player::getProjectiles() {
    return currentWeapon->getProjectiles();
}

float Player::getMaxSpeed() const {
    return maxSpeed;
}

void Player::setMaxSpeed(float maxSpeed) {
    this->maxSpeed = maxSpeed;
}

int Player::getMaxHealth() const {
    return maxHealth;
}

void Player::setMaxHealth(int maxHealth) {
    this->maxHealth = maxHealth;
}
