#ifndef LEFT2DIE_GAME_H
#define LEFT2DIE_GAME_H

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Font.hpp>
#include "states/StateMachine.h"
#include "util/ResourceLoader.h"

typedef std::string String;

class StateMachine;

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

    sf::Font& getFont() const { return *font; }
    sf::RenderWindow& getWindow() const { return *window; }
    StateMachine& getStateMachine() const {return *stateMachine; }

protected:
    unsigned int width, height;
    String title;
    bool running;

    StateMachine* stateMachine;

    sf::RenderWindow* window;

    sf::Font* font;
};


#endif //LEFT2DIE_GAME_H
