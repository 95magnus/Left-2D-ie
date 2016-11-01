#ifndef LEFT2DIE_STATEMAINMENU_H
#define LEFT2DIE_STATEMAINMENU_H

#include "StateBase.h"
#include "../Game.h"
#include "../GUI/Button.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/OpenGL.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>


typedef std::string String;

class StateMainMenu : public StateBase{
public:
    StateMainMenu(Game *game);

    virtual ~StateMainMenu();

    virtual void update();
    virtual void draw();

    void createButton(sfg::Button::Ptr buttonName, const sf::Vector2f &position);
  //  inline void setButtonColor(const String& s, const sf::Color &color, const sf::Color &prelight);

    void buttonPlayClicked();
    void buttonHiscoresClicked();
    void buttonSettingsClicked();
    void buttonQuitClicked();

protected:
    sf::Vector2f position;
    sfg::Button::Ptr buttonName;

    sfg::Button::Ptr invisibleButton;
    sfg::Button::Ptr playButton;
    sfg::Button::Ptr hiscoresButton;
    sfg::Button::Ptr settingsButton;
    sfg::Button::Ptr quitButton;

    Button* button;
    sf::Font *font;
};

#endif //LEFT2DIE_STATEMAINMENU_H
