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

    // We don't use SFML to draw
    window->resetGLStates();
    // Makes the window move weird on Linux for some reason
    // window->setVerticalSyncEnabled(true);

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


sf::Clock timer;

void Game::run() {
    while (window->isOpen() && running)
    {
        sf::Event event;

        while (window->pollEvent(event))
        {
            if( event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased ) {
                event.mouseButton.x %= 400;
                event.mouseButton.y %= 300;
            }
            else if( event.type == sf::Event::MouseMoved ) {
                event.mouseMove.x %= 400;
                event.mouseMove.y %= 300;
            }
            sfgDesktop.HandleEvent(event);
//            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
//                stop();
//
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num0)) {
//                stateMachine->setState(StateMachine::StateID::PLAY_GAME);
//            }
//
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) {
//                stateMachine->setState(StateMachine::StateID::MAIN_MENU);
//            }
//
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) {
//                stateMachine->setState(StateMachine::StateID::SINGLE_PLAYER);
//            }
//
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) {
//                stateMachine->setState(StateMachine::StateID::MULTI_PLAYER);
//            }
//
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4)) {
//                stateMachine->setState(StateMachine::StateID::HIGH_SCORE);
//            }
//
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5)) {
//                stateMachine->setState(StateMachine::StateID::SETTINGS);
//            }
        }
        update();

        draw();
    }
}

void Game::stop() {
    running = false;
    window->close();
}

void Game::update() {
//    sfgDesktop.Update(timer.getElapsedTime().asMilliseconds());
//    timer.restart();
    sfgDesktop.Update(timer.restart().asSeconds());
    stateMachine->update();

}

void Game::draw() {
    window->clear(sf::Color::Black);
    stateMachine->draw();

    sfgui->Display(*window);
    window->display();
}