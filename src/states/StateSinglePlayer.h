#ifndef LEFT2DIE_STATESINGLEPLAYER_H
#define LEFT2DIE_STATESINGLEPLAYER_H

#include <SFML/Graphics/Text.hpp>
#include "../Game.h"
#include "StateBase.h"
#include "../modules/Message.h"

class InputTester;
class Level;
class Message;

class StateSinglePlayer : public StateBase {
public:
    StateSinglePlayer(Game* game);
    virtual ~StateSinglePlayer();

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

protected:
    sf::RenderWindow *window;
    sf::View *view;
    Level* level;
    Message* mb;
};

#endif //LEFT2DIE_STATESINGLEPLAYER_H
