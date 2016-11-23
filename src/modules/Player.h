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

class Player : public PlayerController {
public:
    //public stats
    int speed;
    int x, y;

    // Model
    sf::RectangleShape sprite;
    sf::RectangleShape hitbox;
    sf::Texture texture;

    // Animation rotation arrays, worst implementation, please forgive me

    sf::IntRect left[5] = {{970, 635, 240, 630},
                           {0, 0, 480, 630},
                           {0, 1270, 315, 630},
                           {485, 0, 480, 630},
                           {970, 0, 480, 630}};

    sf::IntRect right[5] = {{1215, 635, 240, 630},
                       {1455, 0, 480, 630},
                       {320, 1270, 315, 630},
                       {0, 635, 480, 630},
                       {485, 635, 480, 630}};

    sf::IntRect up[5] = {{1195, 1270, 180, 630},
                    {1645, 635, 480, 630},
                     {1645, 635, 480, 630},
                    {1010, 1270, 180, 630},
                    {1010, 1270, 180, 630}};

    sf::IntRect down[5] = {{1460, 635, 180 ,630},
                      {640, 1270, 180, 630},
                      {825, 1270, 180, 630},
                      {825, 1270, 180, 630},
                      {640, 1270, 180, 630}};




    // Sounds
    sf::SoundBuffer SBuffer;
    sf::Sound sound;

    // Actions
    void moveUp(float dt);
    void moveDown(float dt);
    void moveRight(float dt);
    void moveLeft(float dt);
    void scale(float x);
    void animationCycler(sf::IntRect dir[5]);

    void update(float deltaTime);
    void draw(sf::RenderWindow &window);

    //Inventory

    /*
     * TODO: Add weapon actions
    void primaryWeapon;
    void secondaryWeapon;
    void specialWeapon;
     */
    void death();
    void hit();
    Player(InputManager* inputManager);
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
    float scaleFactor;
    sf::Clock clock;
    bool moving;
    enum Direction {Left, Right, Up, Down};
    Direction currentDir;
    sf::Vector2f xy;

    // Inventory
    // TODO: 3 plasser o "bagen" til våpenobjekter
    // TODO: 1 primary, 1 secondary å 1 special

};


#endif //LEFT2DIE_PLAYER_H
