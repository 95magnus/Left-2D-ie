#ifndef LEFT2DIE_STATESHOP_H
#define LEFT2DIE_STATESHOP_H

#include "StateBase.h"
#include "../Game.h"

#include <SFML/Graphics/Text.hpp>

typedef std::string String;

class StateShop : public StateBase{
public:
    StateShop(Game* game);
    virtual ~StateShop();

    void update(float deltaTime);
    void draw();

    void resume();
    void pause();

    void initShopGui();

    void createImage(sfg::Image::Ptr image, const String &filename);

protected:
    sf::Font *font;
    sfg::Window::Ptr shopWindow;

    sfg::Button::Ptr nextButton;

    sfg::Image::Ptr gameover;
};


#endif //LEFT2DIE_STATESHOP_H
