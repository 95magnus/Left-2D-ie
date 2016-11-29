#ifndef LEFT2DIE_STATESINGLEPLAYER_H
#define LEFT2DIE_STATESINGLEPLAYER_H

#include "StateBase.h"
#include "../Game.h"
#include <SFML/Graphics/Text.hpp>

class StateSinglePlayer : public StateBase {
public:
    StateSinglePlayer(Game* game);
    virtual ~StateSinglePlayer();

    virtual void update();
    virtual void draw();

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
};

#endif //LEFT2DIE_STATESINGLEPLAYER_H
