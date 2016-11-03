#ifndef LEFT2DIE_STATEMAINMENU_H
#define LEFT2DIE_STATEMAINMENU_H

#include "StateBase.h"
#include "../Game.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/OpenGL.hpp>


class StateMainMenu : public StateBase {
public:
    StateMainMenu(Game* game);
    virtual ~StateMainMenu();

    void update(float deltaTime);
    void draw();

protected:

};

#endif //LEFT2DIE_STATEMAINMENU_H
