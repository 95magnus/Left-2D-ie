#ifndef LEFT2DIE_ENEMY_H
#define LEFT2DIE_ENEMY_H

#include <math.h>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Player.h"

class Player;

class Enemy : public Entity {
public:

    void buff(int percent);

    void dealDamage(Player *player);

    Enemy(sf::Vector2f spawnPos);
    virtual ~Enemy();

    sf::Texture texture;
    float velX, velY, diffX, diffY, magnitude;
    sf::RectangleShape sprite;
    sf::RectangleShape hitbox;
    sf::RectangleShape collisionBox;

    void update(float deltaTime);
    void update(std::vector<sf::Vector2f> players, float deltaTime);
    void draw(sf::RenderWindow &window);

    void animationCycler(float interval);
    void getHit(int damage);
    sf::IntRect rect[3] = {{335, 0, 300, 600},
                                     {640, 0, 300, 600},
                                     {0, 0, 330, 600}};

    int getHealth() const;
    void setHealth(int health);

    void setTarget(sf::Vector2i pos);
    bool requestingNewTarget() { return requestNewTarget; }


    int getScoreReward() const;
    void setScoreReward(int scoreReward);

protected:
    sf::RectangleShape healthBar;
    sf::RectangleShape hpBarBG;
    sf::Clock cycleClock, attackTimer;

    sf::Vector2i target;

    bool moving, goingRight, requestNewTarget = true;

    int health, maxHealth, damage, speed, scoreReward, hit;
};

#endif //LEFT2DIE_ENEMY_H
