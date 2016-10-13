#ifndef LEFT2DIE_STATEMAINMENU_H
#define LEFT2DIE_STATEMAINMENU_H

#include "StateBase.h"
#include "../Game.h"
#include <SFML/Graphics/Text.hpp>

class StateMainMenu : public StateBase {
public:
    StateMainMenu(Game* game);
    virtual ~StateMainMenu();

    void update();
    void draw();
};

#endif //LEFT2DIE_STATEMAINMENU_H
