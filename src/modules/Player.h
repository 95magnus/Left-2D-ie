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

class Weapon;
class Projectile;

class Player : public PlayerController {
public:
    enum Direction {Up, Down, Left, Right};

    sf::Vector2f move(float deltaTime);

    void scale(float x);
    void animationCycler(std::vector<sf::IntRect> dir);

    void update(float deltaTime);
    void draw(sf::RenderWindow &window);

    void death();
    void hit();
    Player(sf::RenderWindow* window, InputManager &inputManager);
    ~Player();

    void mousePressed(int x, int y, sf::Mouse::Button button);

    // Getters & setters for stats
    int getHealth() const;
    void setHealth(int health);
    int getSpeed() const;
    void setSpeed(int speed);

    Direction getCurrentDir() const;

    void setCurrentDir(Direction currentDir);

    sf::Vector2f getPosition() { return xy; }

    int getScore() const;
    void setScore(int score);
    int getMoney() const;
    void setMoney(int money);
    int getArmor() const;
    void setArmor(int armor);
    int getKills() const;
    void setKills(int kills);
    std::vector<Projectile> *getBullets();

private:
    //Components
    //InputComponent input_;
    //GraphicsComponent graphics_;
    //PhysicsComponent physics_;

    // Sprites

    float speed = 175.0f;
    int x, y;

    sf::RenderWindow* window;

    // Model
    sf::RectangleShape sprite;
    sf::CircleShape shadow;
    sf::RectangleShape hitbox;
    sf::Texture texture;

    // Sounds
    sf::SoundBuffer SBuffer;
    sf::Sound sound;

    // Private Stats
    int health, armor, kills, score, money;
    float scaleFactor;
    sf::Clock clock;
    //Speedclock is to ensure that the player doesnt move faster or slower due to
    //differences in the power/workload the CPU has
    sf::Clock speedClock;
    bool moving;
    Direction currentDir;
    sf::Vector2f xy;

    // Animation rotation arrays, worst implementation, please forgive me

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

    // Inventory
    // TODO: 3 plasser o "bagen" til våpenobjekter
    // TODO: 1 primary, 1 secondary å 1 special
    Weapon* currentWeapon;
    //Inventory
        /*
         * TODO: Add weapon actions
        void primaryWeapon;
        void secondaryWeapon;
        void specialWeapon;
         */
};


#endif //LEFT2DIE_PLAYER_H
