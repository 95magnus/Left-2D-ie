#ifndef LEFT2DIE_STATESHOP_H
#define LEFT2DIE_STATESHOP_H

#include "StateBase.h"
#include "../Game.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/OpenGL.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>


typedef std::string String;


class StateShop {
public:
    StateShop();
    virtual ~StateShop();
    virtual void update();
    virtual void draw();


protected:
    sfg::Button::Ptr invisibleButton;
    sfg::Button::Ptr backButton;

    sf::Font *font;
    sfg::Image::Ptr sfgImage;
    sf::Image* guiImage;

};


#endif //LEFT2DIE_STATESHOP_H
