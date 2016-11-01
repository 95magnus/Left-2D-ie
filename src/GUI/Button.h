#ifndef LEFT2DIE_BUTTON_H
#define LEFT2DIE_BUTTON_H

#include "SFGUI/Widgets.hpp"
#include "../states/StateBase.h"

class Game;

class Button {
public:
    Button(sfg::Button::Ptr button);
    virtual ~Button();
    virtual void update();
    virtual void draw(sfg::Button::Ptr buttonName, const sf::Vector2f &position);

    //void createButton(sfg::Button::Ptr buttonName, const sf::Vector2f &position);

protected:
    sf::Vector2f position;
    sfg::Button::Ptr buttonName;

    sfg::Desktop* desktop;
    StateBase* stateBase;
};


#endif //LEFT2DIE_BUTTON_H
