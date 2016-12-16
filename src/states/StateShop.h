#ifndef LEFT2DIE_STATESHOP_H
#define LEFT2DIE_STATESHOP_H

#include "StateBase.h"
#include "../Game.h"
#include "../entities/Weapon.h"

#include <SFML/Graphics/Text.hpp>

typedef std::string String;

class Player;

class StateShop : public StateBase {
public:
    StateShop(Game* game);
    virtual ~StateShop();
    void update(float deltaTime);
    void draw(sf::RenderWindow &window);

    void resume();
    void pause();

    void initShopGui();

    void initGameGui();

    void upgradeWeapon();
    void upgradeFireRate();
    void upgradeDamage();
    void upgradeHealth();

protected:
    sf::Font *font;

    sf::Text* nextRoundLabel;
    sf::Text* totalCoins;
    sf::Text* cost;
    sf::Text* totalCoinsEarnedLabel;

    sf::Text* currentWeaponName;
    sf::Text* currentWeaponLabel;

    sf::Text* upgradedWeaponName;
    sf::Text* upgradeWeaponLabel;
    sf::Text* currentFireRateLabel;
    sf::Text* upgradeFireRateLabel;
    sf::Text* currentDamageLabel;
    sf::Text* upgradeDamageLabel;
    sf::Text* currentHealthLabel;
    sf::Text* upgradeHealthLabel;

    sf::Text* currentFireRateValue;
    sf::Text* upgradedFireRateValue;
    sf::Text* currentDamageValue;
    sf::Text* upgradedDamageValue;
    sf::Text* currentHealthValue;
    sf::Text* upgradedHealthValue;

    sf::Text* upgradeWeaponCost;
    sf::Text* upgradeFireRateCost;
    sf::Text* upgradeDamageCost;
    sf::Text* upgradeHealthCost;

    sf::RectangleShape* inventoryContainer;
    sf::RectangleShape* fireRateContainer;
    sf::RectangleShape* damageContainer;
    sf::RectangleShape* healthContainer;
    sf::RectangleShape* coinsContainer;

    sf::Sprite currentWeaponImage, nextWeaponImage;

    Player* player;
    Weapon* weapon;

    sfg::Window::Ptr singlePlayerWindow;

    int weaponCost = 700;
    int fireRateCost = 350;
    int damageCost = 100;
    int healthCost = 350;

    std::vector<sf::Texture*> weaponImages;
    int weaponStage;

    std::vector<String> upgradedThemePath = {
            "resources/gui/resized_shotgun.png",
            "resources/gui/resized_tommygun.png",
            "resources/gui/resized_rifle.png",
            "resources/gui/resized_sniper.png",
            "resources/gui/resized_raygun.png"
    };
};

#endif //LEFT2DIE_STATESHOP_H
