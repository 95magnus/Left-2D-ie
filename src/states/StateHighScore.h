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

    void buttonBackClicked();

    void pause();
    void resume();
    void initButtons();

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
