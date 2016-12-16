#ifndef LEFT2DIE_STATESINGLEPLAYER_H
#define LEFT2DIE_STATESINGLEPLAYER_H

#include <memory>
#include <SFML/Graphics/Text.hpp>
#include "../Game.h"
#include "StateBase.h"
#include "../gui/Message.h"
#include <math.h>
#include "SFML/Audio.hpp"
//#include "../entities/NormalZombie.h"
//#include "../entities/Enemy.h"

class World;
class Message;
class Level;
class Player;
//class NormalZombie;
class Enemy;
class Projectile;

class StateSinglePlayer : public StateBase {
public:
    StateSinglePlayer(Game* game);
    virtual ~StateSinglePlayer();

    void init();

    void update(float deltaTime);
    void draw(sf::RenderWindow &window);

    void pause();
    void resume();

    void spawnWave();
    void getCurrentWeaponImage();
    void getUpgradedWeaponImage();

    void initGameGui();
    void pauseGameGui();
    void goToShop();

    void checkForHits(std::vector<Enemy*> &enemies, std::vector<Projectile> &bullets);

    void gameOver();

    Player* getPlayer(){
        return player;
    }

    sf::Color interpolateColors(sf::Color c1, sf::Color c2, float mixPercent);

protected:
    //InputManager* inputManager;

    sf::RenderWindow *window;
    sf::View *view;
    Level* level;
    int waveNumber;
    std::string waveMsg;
    sf::RectangleShape vignette;
    sf::Texture vignetteText;
    Player* player;
    std::vector<Player*> players;
    std::vector<Enemy*> enemies;
    std::vector<sf::Vector2f> playerPositions;
    Enemy* zombie;

    Message* mb;

private:
    String levelFileName = "level_1.l2d";

    sf::RectangleShape screenFade;
    sf::Text pauseText;

    World* world;

    sf::RectangleShape* coinsContainer;


    sf::RectangleShape* hpGreenBar;
    sf::RectangleShape* hpRedBar;

    sf::Font* font;
    sf::Text* score;
    sf::Text* coins;

    sf::Text zombiesLeft;
    int zombieCounter;

    sf::SoundBuffer musicBuffer;
    sf::Sound music;

    String currentWeaponImage;
    String upgradedWeaponImage;

    bool initialized = false;

//    String currentWeapon[] = {"resources/gui/ak.png", "resources/gui/shotgun.png", "resources/gui/tommygun.png",
//                              "resources/gui/rifle.png", "resources/gui/sniper.png", "resources/gui/raygun.png"};
};

#endif //LEFT2DIE_STATESINGLEPLAYER_H
