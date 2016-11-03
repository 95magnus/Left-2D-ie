#ifndef LEFT2DIE_STATESINGLEPLAYER_H
#define LEFT2DIE_STATESINGLEPLAYER_H

#include <SFML/Graphics/Text.hpp>
#include "../Game.h"
#include "StateBase.h"

class InputTester;
class Level;

class StateSinglePlayer : public StateBase {
public:
    StateSinglePlayer(Game* game);
    virtual ~StateSinglePlayer();

    void update(float deltaTime);
    void draw();
protected:
    Level* level;
};

#endif //LEFT2DIE_STATESINGLEPLAYER_H
