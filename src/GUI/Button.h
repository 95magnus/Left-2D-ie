#ifndef LEFT2DIE_BUTTON_H
#define LEFT2DIE_BUTTON_H

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include "../util/ResourceLoader.h"
#include <SFML/Graphics/RenderWindow.hpp>

typedef std::string String;


class Button : public sf::Drawable{
public:
    Button(const unsigned int width, const unsigned int height, const String &title);

    Button();

    virtual ~Button();

    void ButtonClicked();
    void TypeClicked();
    void Draw();

    sf::Image& getImage() const { return *image;}

private:
    unsigned int width, height;
    String title;


    sfg::SFGUI sfgui;

    sfg::Button::Ptr buttonSelect;
    sfg::Button::Ptr selectBox;

    // Add picture to buttons
    sfg::Label::Ptr sfgLabel;

    sfg::Box::Ptr tileSelect;

    sfg::Alignment::Ptr selectAlignment;

    sf::Image* image;

};


#endif //LEFT2DIE_BUTTON_H
