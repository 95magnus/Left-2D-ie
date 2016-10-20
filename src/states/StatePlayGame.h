#ifndef LEFT2DIE_STATEPLAYGAME_H
#define LEFT2DIE_STATEPLAYGAME_H

#include "StateBase.h"
#include "../Game.h"
#include <SFML/Graphics/Text.hpp>

class StatePlayGame : public StateBase {
public:
    StatePlayGame(Game* game);
    virtual ~StatePlayGame();

    void update();
    void draw();
protected:

};


#endif //LEFT2DIE_STATEPLAYGAME_H
