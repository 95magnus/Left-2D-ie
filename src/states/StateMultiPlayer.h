#ifndef LEFT2DIE_STATEMULTIPLAYER_H
#define LEFT2DIE_STATEMULTIPLAYER_H

#include "StateBase.h"
#include "../Game.h"
#include <SFML/Graphics/Text.hpp>

class StateMultiPlayer : public StateBase {
public:
    StateMultiPlayer(Game* game);
    virtual ~StateMultiPlayer();

    void update();
    void draw();
};

#endif //LEFT2DIE_STATEMULTIPLAYER_H
