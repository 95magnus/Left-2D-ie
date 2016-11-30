#ifndef LEFT2DIE_STATEBASE_H
#define LEFT2DIE_STATEBASE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFGUI/Desktop.hpp>
#include <SFGUI/Button.hpp>

class Game;
typedef std::string String;

class StateBase {
public:
    virtual ~StateBase();

    virtual void init() {}

    virtual void update(float deltaTime) = 0;
    virtual void draw() = 0;

    virtual void pause() { paused = true; }
    virtual void resume() { paused = false; }
    virtual void switchedState() {};

    sfg::Desktop* getDesktop() const { return desktop; }
    void updateDesktop();
    virtual void createButton(sfg::Button::Ptr buttonName, const sf::Vector2f &position);

    sfg::Desktop* desktop;

protected:
    StateBase(Game* game);

    Game* game;

    sf::Clock timer;

    const String themePath = "resources/gui/theme.css";

    bool paused;
};

#endif //LEFT2DIE_STATEBASE_H
