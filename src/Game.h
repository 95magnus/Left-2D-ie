#ifndef LEFT2DIE_GAME_H
#define LEFT2DIE_GAME_H

#include <SFML/Config.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "states/StateMachine.h"
#include "level/Level.h"
#include "util/ResourceLoader.h"
#include "SFGUI/SFGUI.hpp"

typedef std::string String;

class StateMachine;
class InputManager;
class InputTester;

class Game {
public:
    Game(const unsigned int width, const unsigned int height, const String &title);
    virtual ~Game();

    void init();

    void start();
    void run();
    void stop();

    void update(float deltaTime);
    void draw();

    sf::Font& getFont() const { return *font; }
    sf::RenderWindow& getWindow() const { return *window; }
    StateMachine& getStateMachine() const { return *stateMachine; }
    InputManager& getInputManager() const { return *inputManager; }
    sf::Vector2f getWindowCenter() const {
        return sf::Vector2f(getWindow().getSize().x/2, getWindow().getSize().y/2);
    };

protected:
    const unsigned int updatesPerSecond = 60;
    unsigned int width, height;
    String title;
    bool running;

    InputTester* inputTester;

    StateMachine* stateMachine;
    InputManager* inputManager;

    sf::RenderWindow* window;
    sf::Font* font;
};


#endif //LEFT2DIE_GAME_H
