#ifndef LEFT2DIE_STATEHIGHSCORE_H
#define LEFT2DIE_STATEHIGHSCORE_H

#include "StateBase.h"
#include "../Game.h"
#include <SFML/Graphics/Text.hpp>

class StateHighScore : public StateBase {
public:
    StateHighScore(Game* game);
    virtual ~StateHighScore();

    void update(float deltaTime);
    void draw();

    void pause();
    void resume();
    void initButtons();

    void buttonBackClicked();

protected:
    sf::Font *font;
    sfg::Image::Ptr sfgImage;
    sf::Image* guiImage;

};

#endif //LEFT2DIE_STATEHIGHSCORE_H
