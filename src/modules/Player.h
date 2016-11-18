//
// Created by Eivind Hystad on 14/10/2016.
//

#ifndef LEFT2DIE_PLAYER_H
#define LEFT2DIE_PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Player {
public:
    //public stats
    int speed;
    int x, y;

    // Model
    sf::RectangleShape sprite;
    sf::RectangleShape hitbox;

    // Sounds
    sf::SoundBuffer SBuffer;
    sf::Sound sound;

    // Actions
    void moveUp(float dt);
    void moveDown(float dt);
    void moveRight(float dt);
    void moveLeft(float dt);
    /*
     * TODO: Add weapon actions
    void primaryWeapon;
    void secondaryWeapon;
    void specialWeapon;
     */
    void death();
    void hit();
    Player();
    ~Player();

    // Getters & setters for stats
    int getHealth() const;
    void setHealth(int health);
    int getSpeed() const;
    void setSpeed(int speed);
    int getScore() const;
    void setScore(int score);
    int getMoney() const;
    void setMoney(int money);
    int getArmor() const;
    void setArmor(int armor);
    int getKills() const;
    void setKills(int kills);

private:
    //Components
    //InputComponent input_;
    //GraphicsComponent graphics_;
    //PhysicsComponent physics_;

    // Sprites


    // Private Stats
    int health;
    int armor;
    int kills;
    int score;
    int money;

    // Inventory
    // TODO: 3 plasser o "bagen" til våpenobjekter
    // TODO: 1 primary, 1 secondary å 1 special

};


#endif //LEFT2DIE_PLAYER_H
