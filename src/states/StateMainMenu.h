#ifndef LEFT2DIE_STATEMAINMENU_H
#define LEFT2DIE_STATEMAINMENU_H

#include "StateBase.h"
#include "../Game.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/OpenGL.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>


typedef std::string String;

class StateMainMenu : public StateBase{
public:
    StateMainMenu(Game *game);
    virtual ~StateMainMenu();

    void update();
    void draw();

 //   void loadButton(const sfg::Button::Ptr buttonName, const String &filename);
    void createButton(sfg::Button::Ptr buttonName, const sf::Vector2f &position, const String &filename);
  //  void setButtonPosition(const sfg::Button::Ptr buttonName, const sf::Vector2f &position);

    //void buttonClicked(const sfg::Button::Ptr buttonName);
    void buttonClicked();

protected:
    String filename;
   // sf::Image* guiImage;
    sf::Vector2f position;
    sfg::Image::Ptr sfgImage;

    sfg::Button::Ptr buttonName;
    sfg::Button::Ptr playButton;
    sfg::Button::Ptr hiscoresButton;
    sfg::Button::Ptr settingsButton;
    sfg::Button::Ptr quitButton;

    sfg::Desktop *sfgDesktop;

};

#endif //LEFT2DIE_STATEMAINMENU_H
