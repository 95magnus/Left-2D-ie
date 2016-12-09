#ifndef LEFT2DIE_STATESINGLEPLAYER_H
#define LEFT2DIE_STATESINGLEPLAYER_H

#include <SFML/Graphics/Text.hpp>
#include "../Game.h"
#include "StateBase.h"
#include "../modules/Message.h"
//#include "../modules/NormalZombie.h"
//#include "../modules/Enemy.h"

class Message;
class Level;
class Player;
//class NormalZombie;
class Enemy;

class StateSinglePlayer : public StateBase {
public:
    StateSinglePlayer(Game* game);
    virtual ~StateSinglePlayer();

    void init();

    void update(float deltaTime);
    void draw();

    void pause();
    void resume();

    void initGameGui();
    void pauseGameGui();
    void goToShop();

    void onItemOneBoxMarked();
    void onItemTwoBoxMarked();
    void onItemThreeBoxMarked();
    void onItemFourBoxMarked();
    void onItemFiveBoxMarked();
    void onItemSixBoxMarked();

    void onAbilityOneBoxMarked();
    void onAbilityTwoBoxMarked();
    void onAbilityThreeBoxMarked();
    void onAbilityFourBoxMarked();

    void createImage(sfg::Image::Ptr image, const String &filename);

protected:
    //InputManager* inputManager;

    sf::RenderWindow *window;
    sf::View *view;
    Level* level;

    Player* player;
    std::vector<Player*> players;
    Enemy* zombie;
    Message* mb;

private:
    sf::RectangleShape* coinsContainer;
    sf::RectangleShape* hpGreenBar;
    sf::RectangleShape* hpRedBar;

    sf::Font* font;

    sf::Text* score;
    sf::Text* coins;

    sfg::Image::Ptr hpBar;
    sfg::Image::Ptr coinsBar;
    sfg::Image::Ptr playerBar;

    sfg::Label::Ptr zombieLeft;

    sfg::Button::Ptr itemOne;
    sfg::Button::Ptr itemTwo;
};

#endif //LEFT2DIE_STATESINGLEPLAYER_H
