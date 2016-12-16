//
// Created by Eivind Hystad on 14/10/2016.
//

#ifndef LEFT2DIE_PLAYER_H
#define LEFT2DIE_PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Game.h"
#include "../input/InputObserver.h"
#include "../input/PlayerController.h"
#include "Weapon.h"
#include "Projectile.h"
#include "Entity.h"

class Weapon;
class Projectile;

class Player : public Entity, PlayerController {
public:

    enum Direction { Up, Down, Left, Right };

    Player(sf::RenderWindow &window, sf::View &view, InputManager &inputManager, sf::Vector2f pos);
    ~Player();

    void update(float deltaTime);
    void draw(sf::RenderWindow &window);

    sf::Vector2f move(float deltaTime);

    void scale(float x);
    void animationCycler(std::vector<sf::IntRect> dir);

    void hit();
    void onDeath();

    int getHealth() const;
    void setHealth(int health);
    int getSpeed() const;
    void setSpeed(int speed);

    Direction getCurrentDir() const;
    void setCurrentDir(Direction currentDir);

    sf::Vector2f getPosition() { return xy; }
    sf::FloatRect getBounds() { return collisionBox; }

    void addScore(int add) { money += add; score += add; }

    int getScore() const;
    void setScore(int score);
    int getMoney() const;
    void setMoney(int money);
    int getArmor() const;
    void setArmor(int armor);
    int getKills() const;
    void setKills(int kills);
    std::vector<Projectile*>& getProjectiles();

    int getMaxHealth() const;
    void setMaxHealth(int maxHealth);

    float getMaxSpeed() const;
    void setMaxSpeed(float maxSpeed);

    Weapon* getWeapon() { return currentWeapon; }

private:
    float maxSpeed = 175.0f;
    float speed = 175.0f;
    int x, y, hitColor;

    sf::RenderWindow &window;
    sf::View &view;
    sf::Texture graveStone;

    // Model
    sf::RectangleShape sprite;
    sf::CircleShape shadow;
    sf::RectangleShape hitbox;
    sf::Texture texture;

    sf::FloatRect collisionBox;

    // Sounds
    sf::SoundBuffer hitBuffer, diedBuffer;
    sf::Sound hitSound, deathSound;

    int health, armor, kills, score, money, maxHealth;
    float scaleFactor;
    sf::Clock clock;
    //Speedclock is to ensure that the player doesnt move faster or slower due to
    //differences in the power/workload the CPU has
    sf::Clock speedClock;
    bool moving;
    Direction currentDir;
    sf::Vector2f xy;

    Weapon* currentWeapon;

    std::vector<sf::IntRect> left = {{970, 635, 240, 630},
                           {0, 0, 480, 630},
                           {0, 1270, 315, 630},
                           {485, 0, 480, 630},
                           {970, 0, 480, 630}};

    std::vector<sf::IntRect> right = {{1215, 635, 240, 630},
                            {1455, 0, 480, 630},
                            {320, 1270, 315, 630},
                            {0, 635, 480, 630},
                            {485, 635, 480, 630}};

    std::vector<sf::IntRect> up = {{1195, 1270, 180, 630},
                         {1645, 635, 480, 630},
                         {1645, 635, 480, 630},
                         {1010, 1270, 180, 630},
                         {1010, 1270, 180, 630}};

    std::vector<sf::IntRect> down = {{1460, 635, 180 ,630},
                            {640, 1270, 180, 630},
                            {825, 1270, 180, 630},
                            {825, 1270, 180, 630},
                            {640, 1270, 180, 630}};;

    std::map<Direction, std::vector<sf::IntRect>> animationDirections;

};


#endif //LEFT2DIE_PLAYER_H
