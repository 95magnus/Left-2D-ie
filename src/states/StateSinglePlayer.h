#ifndef LEFT2DIE_STATESINGLEPLAYER_H
#define LEFT2DIE_STATESINGLEPLAYER_H

#include <memory>
#include <SFML/Graphics/Text.hpp>
#include "../Game.h"
#include "StateBase.h"
#include "../gui/Message.h"
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
