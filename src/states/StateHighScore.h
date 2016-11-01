#ifndef LEFT2DIE_STATEHIGHSCORE_H
#define LEFT2DIE_STATEHIGHSCORE_H

#include "StateBase.h"
#include "../Game.h"
#include <SFML/Graphics/Text.hpp>

class StateHighScore : public StateBase {
public:
    StateHighScore(Game* game);
    virtual ~StateHighScore();

    void update();
    void draw();

    void createButton(sfg::Button::Ptr buttonName, const sf::Vector2f &position);
    void buttonBackClicked();

protected:
    String filename;
    sf::Vector2f position;

    sfg::Button::Ptr buttonName;
    sfg::Button::Ptr invisibleButton;
    sfg::Button::Ptr backButton;

    sf::Font *font;
    sfg::Image::Ptr sfgImage;
    sf::Image* guiImage;

};

#endif //LEFT2DIE_STATEHIGHSCORE_H
