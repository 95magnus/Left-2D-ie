#ifndef LEFT2DIE_STATESETTINGS_H
#define LEFT2DIE_STATESETTINGS_H

#include "StateBase.h"
#include "../Game.h"
#include <SFML/Graphics/Text.hpp>

class StateSettings : public StateBase {
public:
    StateSettings(Game* game);
    virtual ~StateSettings();

    void update();
    void draw();
};

#endif //LEFT2DIE_STATESETTINGS_H
