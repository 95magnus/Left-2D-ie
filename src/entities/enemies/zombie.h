#ifndef LEFT2DIE_ZOMBIE_H
#define LEFT2DIE_ZOMBIE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Zombie {
public:
    // Models
    sf::RectangleShape zom;
    sf::RectangleShape hitbox;
    sf::RectangleShape sprite;

    // Sound elements
    sf::SoundBuffer SBuffer;
    sf::Sound sound;


    // Move Actions
    void moveUp(float dt);
    void moveDown(float dt);
    void moveRight(float dt);
    void moveLeft(float dt);


    void death();
    void hit();
    Zombie();
    virtual ~Zombie();

    // Getters & setters
    int getHealth() const;
    void setHealth(int health);
    int getSpeed() const;
    void setSpeed(int speed);



private:
    int health;
    int speed;
    int armor;

};


#endif //LEFT2DIE_ZOMBIE_H
