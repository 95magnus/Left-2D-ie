#ifndef LEFT2DIE_STATEMULTIPLAYER_H
#define LEFT2DIE_STATEMULTIPLAYER_H

#include "StateBase.h"
#include "../Game.h"
#include <SFML/Graphics/Text.hpp>

class World;

class StateMultiPlayer : public StateBase {
public:
    StateMultiPlayer(Game* game);
    virtual ~StateMultiPlayer();

    void update(float deltaTime);
    void draw(sf::RenderWindow &window);

protected:
    String levelFileName = "testLevel.l2d";

    World* world;
};

#endif //LEFT2DIE_STATEMULTIPLAYER_H
