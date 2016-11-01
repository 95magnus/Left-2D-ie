#ifndef LEFT2DIE_STATEBASE_H
#define LEFT2DIE_STATEBASE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFGUI/Desktop.hpp>

class Game;

class StateBase {
public:
    virtual ~StateBase();

    //virtual void init() = 0;

    virtual void update() = 0;
    virtual void draw() = 0;

    virtual void pause() { paused = true; }
    virtual void resume() { paused = false; }

    sfg::Desktop* getDesktop() const { return desktop; }
    void updateDesktop();
    sfg::Desktop* desktop;

protected:
    StateBase(Game* game);

    Game* game;

    sf::Clock timer;


    bool paused;
};

#endif //LEFT2DIE_STATEBASE_H
