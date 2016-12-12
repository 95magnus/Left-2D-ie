#ifndef LEFT2DIE_STATESHOP_H
#define LEFT2DIE_STATESHOP_H

#include "StateBase.h"
#include "../Game.h"

#include <SFML/Graphics/Text.hpp>

typedef std::string String;

class StateShop : public StateBase {
public:
    StateShop(Game* game);
    virtual ~StateShop();
    void update(float deltaTime);
    void draw(sf::RenderWindow &window);

    void resume();
    void pause();

    void initShopGui();

protected:
    sf::Font *font;
    sfg::Image::Ptr sfgImage;
    sf::Image* guiImage;

};


#endif //LEFT2DIE_STATESHOP_H
