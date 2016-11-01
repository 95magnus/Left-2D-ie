#ifndef LEFT2DIE_STATEPLAYGAME_H
#define LEFT2DIE_STATEPLAYGAME_H

#include "../Game.h"
#include <SFML/Graphics/Text.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include "StateBase.h"

typedef std::string String;
class StateMainMenu;

class StatePlayGame : public StateBase{
public:
    StatePlayGame(Game *game);
    virtual ~StatePlayGame();

    void update();
    void draw();

    void createButton(sfg::Button::Ptr buttonName, const sf::Vector2f &position);

    void buttonSinglePlayerClicked();
    void buttonMultiplayerClicked();
    void buttonBackClicked();

protected:
    String filename;
    sf::Vector2f position;

    sfg::Button::Ptr buttonName;
    sfg::Button::Ptr invisibleButton;
    sfg::Button::Ptr singlePlayerButton;
    sfg::Button::Ptr multiplayerButton;
    sfg::Button::Ptr backButton;

    sf::Font *font;

    StateMainMenu* stateMainMenu;
};


#endif //LEFT2DIE_STATEPLAYGAME_H
