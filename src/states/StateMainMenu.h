#ifndef LEFT2DIE_STATEMAINMENU_H
#define LEFT2DIE_STATEMAINMENU_H

#include "StateBase.h"
#include "../Game.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>


typedef std::string String;

class StateMainMenu : public StateBase {
public:
    StateMainMenu(Game *game);
    virtual ~StateMainMenu();

    virtual void update(float deltaTime);
    virtual void draw(sf::RenderWindow &window);

    void pause();
    void resume();
    void initButtons();

    void buttonPlayClicked();
    void buttonHiscoresClicked();
    void buttonSettingsClicked();
    void buttonQuitClicked();

protected:
    sf::RectangleShape background;
    sf::Texture* backgroundImage;

    sf::SoundBuffer soundBufferMain;
    sf::Sound soundMain;
};

#endif //LEFT2DIE_STATEMAINMENU_H
