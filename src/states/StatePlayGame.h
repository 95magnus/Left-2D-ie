#ifndef LEFT2DIE_STATEPLAYGAME_H
#define LEFT2DIE_STATEPLAYGAME_H

#include "../Game.h"
#include <SFML/Graphics/Text.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include "StateBase.h"

typedef std::string String;

class StatePlayGame : public StateBase{
public:
    StatePlayGame(Game *game);
    virtual ~StatePlayGame();

    void update(float deltaTime);
    void draw();

    void resume();
    void pause();
    void initButtons();

    void buttonSinglePlayerClicked();
    void buttonMultiplayerClicked();
    void buttonBackClicked();

protected:
    sf::Font *font;
};


#endif //LEFT2DIE_STATEPLAYGAME_H
