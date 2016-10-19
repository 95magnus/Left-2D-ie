#include "Game.h"

#define DEBUG 1

Game::Game(const unsigned int width, const unsigned int height, const String &title) {
    this->width = width;
    this->height = height;
    this->title = title;

    init();
}

Game::~Game() {
    delete stateMachine;
    delete window;
    delete font;
}

void Game::init() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;

    window = new sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close, settings);

    // Makes the window move weird on Linux for some reason
    // window->setVerticalSyncEnabled(true);

    // window->setActive(true);

    window->setFramerateLimit(60);

    stateMachine = new StateMachine(this);
    font = new sf::Font();

    ResourceLoader loader("resources/");

#if DEBUG
    loader.loadFont(font, "deathrattlebb_reg.ttf"); // Font source: http://www.1001fonts.com/deathrattle-bb-font.html
#else
    font = &loader.loadFont("deathrattlebb_reg.ttf");
#endif

}

void Game::start() {
    running = true;

    run();
}


void Game::run() {
    sf::Clock clock;

    while (window->isOpen() && running)
    {
        sf::Event event;

        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                stop();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) {
                stateMachine->setState(StateMachine::StateID::MAIN_MENU);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) {
                stateMachine->setState(StateMachine::StateID::SINGLE_PLAYER);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) {
                stateMachine->setState(StateMachine::StateID::MULTI_PLAYER);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4)) {
                stateMachine->setState(StateMachine::StateID::HIGH_SCORE);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5)) {
                stateMachine->setState(StateMachine::StateID::SETTINGS);
            }
            else{
                desktop.HandleEvent(event);
            }
        }

        desktop.Update(clock.restart().asMicroseconds());
        update();
        draw();
    }
}

void Game::stop() {
    running = false;
    window->close();
}

void Game::update() {
    stateMachine->update();
}

void Game::draw() {
    window->clear(sf::Color::Black);
    stateMachine->draw();

    sfgui.Display(*window);
    window->display();
}