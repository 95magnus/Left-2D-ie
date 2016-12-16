//
// Created by Eivind Hystad on 20/11/2016.
//

#ifndef LEFT2DIE_WEAPON_H
#define LEFT2DIE_WEAPON_H


#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <cmath>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include "Projectile.h"

class Weapon : public Entity {
public:
//    int penetration;
    Weapon(sf::RenderWindow &window, int wepStage, int damage, float rps, bool spray, int posX, int posY);
    virtual ~Weapon();

    void update(float deltaTime);

    void draw(sf::RenderWindow &window);

    void fire();

    void flipRight();

    void flipLeft();

    void rotateWeapon(int mouseWorldPosX, int mouseWorldPosY);

    void setPosition(int x, int y);

    int getDamage() const;

    void setDamage(int damage);

    float getAngle() const;

    void setAngle(float angle);

    int getWeaponStage() const;

    void setWeaponStage(int weaponStage);

    const sf::RectangleShape &getSprite() const;

    void setSprite(const sf::RectangleShape &sprite);

    const sf::IntRect &getSpriteFront() const;

    void setSpriteFront(const sf::IntRect &spriteFront);

    const sf::IntRect &getSpriteSide() const;

    void setSpriteSide(const sf::IntRect &spriteSide);

    const sf::Texture &getTexture() const;

    void setTexture(const sf::Texture &texture);

    const sf::Texture &getProjectileTexture() const;

    const sf::Texture *getText() const;

    void setProjectileTexture(const sf::Texture &projectileTexture);

    const sf::Mouse &getMouse() const;

    void setMouse(const sf::Mouse &mouse);

    const sf::Clock &getClock() const;

    void setClock(const sf::Clock &clock);

    float getRps() const;

    void setRps(float rps);

    bool isSpray() const;

    void setSpray(bool spray);

    const sf::IntRect *getWeaponStageIntRectsSide() const;

    const sf::IntRect *getWeaponStageIntRectsFront() const;

    const sf::IntRect *getProjectileIntRect() const;

    std::vector<Projectile> &getBullets();


private:
    sf::RenderWindow &window;

    int damage;
    float angle;
    int weaponStage;
    sf::RectangleShape sprite;
    sf::IntRect spriteFront;
    sf::IntRect spriteSide;
    sf::Texture texture;
    sf::Texture projectileTexture;
    sf::Mouse mouse;
    sf::Clock clock;
    float rps;
    bool spray;
    sf::SoundBuffer soundBuffer;
    sf::Sound sound;
    std::vector<Projectile> bullets;

    /* Weapon list 1 to 6
     * 1: AK
     * 2: shotgun
     * 3: tommygun
     * 4: riflerr
     * 5: sniper
     * 6: raygun
     * */
    sf::IntRect weaponStageIntRectsSide[6] = {sf::IntRect(0, 0, 360, 90),
                                              sf::IntRect(465, 255, 195, 60),
                                              sf::IntRect(495, 0, 240, 90),
                                              sf::IntRect(0, 255, 315, 60),
                                              sf::IntRect(0, 0, 465, 155),
                                             sf::IntRect(0, 95, 270, 165)};


    sf::Texture text[6];

    /*
    sf::IntRect weaponStageIntRectsFront[6] = {sf::IntRect(365, 0, 30, 75),
                                               sf::IntRect(0, 0, 360, 90),
                                               sf::IntRect(0, 0, 360, 90),
                                               sf::IntRect(0, 0, 360, 90),
                                               sf::IntRect(0, 0, 360, 90),
                                              sf::IntRect(0, 265, 165, 165)};
    */

    int yOffset[6] = {5, 0, 6, 3, 3, 0};

    sf::IntRect projectileIntRect[6] = {sf::IntRect(140, 140, 90, 45),
                                        sf::IntRect(140, 140, 90, 45),
                                        sf::IntRect(140, 140, 90, 45),
                                        sf::IntRect(140, 140, 90, 45),
                                        sf::IntRect(140, 140, 90, 45),
                                        sf::IntRect(0, 110, 135, 135)};

    void setBullets(const std::vector<Projectile> &bullets);
};

#endif //LEFT2DIE_WEAPON_H
