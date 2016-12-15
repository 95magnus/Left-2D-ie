//
// Created by Eivind Hystad on 13/12/2016.
//

#ifndef LEFT2DIE_CRAWLINGZOMBIE_H
#define LEFT2DIE_CRAWLINGZOMBIE_H

#include "Enemy.h"

class CrawlingZombie : public Enemy {
public:
    CrawlingZombie(const sf::Vector2f &spawnPos);
    virtual void update(float deltaTime);
    virtual void draw(sf::RenderWindow &window);
    virtual void dealDamage(Player *player);
private:
    bool hanging;
    sf::RectangleShape healthBar;
    sf::RectangleShape hpBarBG;
};


#endif //LEFT2DIE_CRAWLINGZOMBIE_H
