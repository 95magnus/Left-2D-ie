#ifndef LEFT2DIE_STATEMAINMENU_H
#define LEFT2DIE_STATEMAINMENU_H

#include "StateBase.h"
#include "../Game.h"
#include "../GUI/Button.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/OpenGL.hpp>
#include <SFGUI/SFGUI.hpp>


class StateMainMenu : public StateBase{
public:
    StateMainMenu(Game* game);
    virtual ~StateMainMenu();

    void update();
    void draw();
    Button* button;

protected:

};

#endif //LEFT2DIE_STATEMAINMENU_H
