#ifndef LEFT2DIE_STATEBASE_H
#define LEFT2DIE_STATEBASE_H

#include <SFML/Graphics/RenderWindow.hpp>

class Game;

class StateBase {
public:
    StateBase(Game* game);
    virtual ~StateBase() {}

    //virtual void init() = 0;

    virtual void update(float deltaTime) = 0;
    virtual void draw() = 0;

    virtual void pause() { paused = true; }
    virtual void resume() { paused = false; }
protected:
    Game* game;

    bool paused;
};

#endif //LEFT2DIE_STATEBASE_H
