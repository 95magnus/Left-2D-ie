#ifndef LEFT2DIE_GAME_H
#define LEFT2DIE_GAME_H

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "states/StateMachine.h"
#include "util/ResourceLoader.h"
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

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

    void update();
    void draw();

    sfg::Label& getLabel() const { return *label; }
    sf::Font& getFont() const { return *font; }
    sf::RenderWindow& getWindow() const { return *window; }
    StateMachine& getStateMachine() const {return *stateMachine; }
    InputManager& getInputManager() const {return *inputManager; }
    sf::Vector2f getWindowCenter() const {
        return sf::Vector2f(getWindow().getSize().x/2, getWindow().getSize().y/2);
    };

    // Create an SFGUI
    sfg::SFGUI* sfgui;

protected:
    unsigned int width, height;
    String title;
    bool running;

    InputTester* inputTester;
    StateMachine* stateMachine;
    InputManager* inputManager;

    sf::RenderWindow* window;
    sf::Font* font;
    sfg::Label* label;
};


#endif //LEFT2DIE_GAME_H
