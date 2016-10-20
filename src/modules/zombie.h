#ifndef LEFT2DIE_ZOMBIE_H
#define LEFT2DIE_ZOMBIE_H

#include <SFML/Graphics.hpp>

class Zombie {
public:
    // Model
    sf::RectangleShape zom;


    void death();
    Zombie();
    virtual ~Zombie();

    // Getters & setters
    int getHealt() const;

    void setHealt(int health);


private:
    int health;

};


#endif //LEFT2DIE_ZOMBIE_H
