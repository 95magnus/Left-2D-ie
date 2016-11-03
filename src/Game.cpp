#include "Game.h"
#include "states/StateMachine.h"
#include "util/ResourceLoader.h"
#include "input/InputManager.h"
#include "input/InputTester.h"

Game::Game(const unsigned int width, const unsigned int height, const String &title) {
    this->width = width;
    this->height = height;
    this->title = title;

    init();
}

Game::~Game() {
    delete stateMachine;
    delete inputManager;
    delete window;
    delete font;
    delete inputTester;
    delete sfgui;
}

void Game::init() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;

    window = new sf::RenderWindow(
            sf::VideoMode(width, height),
            title,
            sf::Style::Default,
            settings
    );

    // We don't use SFML to draw the main menu
    window->resetGLStates();

    sfgui = new sfg::SFGUI();

    stateMachine = new StateMachine(this);
    inputManager = new InputManager(window, stateMachine);
    font = new sf::Font();

    inputTester = new InputTester(inputManager);

    ResourceLoader loader("resources/");

    // Font source: http://www.1001fonts.com/deathrattle-bb-font.html
    loader.loadFont(font, "deathrattlebb_reg.ttf");
    //font = &loader.loadFont("deathrattlebb_reg.ttf");

    inputTester->setTexture(&loader.loadTexture("player.png"));
}

void Game::start() {
    running = true;

    run();
}

void Game::run() {
    sf::Time timePerUpdate = sf::seconds(1.0f / (float)updatesPerSecond);
    sf::Time lastUpdate = sf::Time::Zero;
    sf::Clock updateClock, frameClock;

    int updates = 0, frames;

    while (window->isOpen() && running) {
        // Returns false when window is close requested
        if (!inputManager->checkForInput()) {
            stop();
        }

        sf::Time deltaTime = updateClock.restart(); // Time since previous update
        lastUpdate += deltaTime;

        while(lastUpdate >= timePerUpdate) {
            lastUpdate -= timePerUpdate;

            //desktop.Update(clock.restart().asMicroseconds());
            update(timePerUpdate.asSeconds());
            updates++;
        }

        draw();
        frames++;

        if (frameClock.getElapsedTime() >= sf::seconds(1.0f)) {
            std::stringstream ss;
            ss << title
               //<< " | UPS: " << updates
               << " - FPS: " << frames;

            window->setTitle(ss.str());

            updates = 0;
            frames = 0;
            frameClock.restart();
        }
    }
}

void Game::stop() {
    running = false;
    window->close();
}


void Game::update(float deltaTime) {
    inputManager->update(deltaTime);
    stateMachine->update(deltaTime);
}

void Game::draw() {
    window->clear(sf::Color::Black);

    stateMachine->draw();
    window->draw(*inputTester);

    sfgui->Display(*window);
    window->display();
}