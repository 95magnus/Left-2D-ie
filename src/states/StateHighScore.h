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
};

#endif //LEFT2DIE_STATEHIGHSCORE_H
