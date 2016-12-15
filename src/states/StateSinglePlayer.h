#ifndef LEFT2DIE_STATESINGLEPLAYER_H
#define LEFT2DIE_STATESINGLEPLAYER_H

#include <memory>
#include <SFML/Graphics/Text.hpp>
#include "../Game.h"
#include "StateBase.h"
#include "../gui/Message.h"
#include <math.h>
//#include "../entities/NormalZombie.h"
//#include "../entities/Enemy.h"

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

    void initGameGui();
    void pauseGameGui();
    void goToShop();

    void checkForHits(std::vector<Enemy*> &enemies, std::vector<Projectile> &bullets);

    void gameOver();

    Player* getPlayer(){
        return player;
    }

    sf::Color interpolate(sf::Color c1, sf::Color c2, float mixPercent) {
        sf::Color col;
        col.r = (sf::Uint8) sqrt((1 - mixPercent) * (c1.r * c1.r) + mixPercent * c2.r * c2.r);
        col.g = (sf::Uint8) sqrt((1 - mixPercent) * (c1.g * c1.g) + mixPercent * c2.g * c2.g);
        col.b = (sf::Uint8) sqrt((1 - mixPercent) * (c1.b * c1.b) + mixPercent * c2.b * c2.b);
        return col;
    }

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
    sf::RectangleShape* coinsContainer;
    sf::RectangleShape* hpGreenBar;
    sf::RectangleShape* hpRedBar;

    sf::Font* font;
    sf::Text* score;
    sf::Text* coins;

    std::string filename;

    sf::Text zombiesLeft;
    int zombieCounter;

    bool initialized = false;
};

#endif //LEFT2DIE_STATESINGLEPLAYER_H
