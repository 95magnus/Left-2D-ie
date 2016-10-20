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
}

void Game::init() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;

    window = new sf::RenderWindow(sf::VideoMode(width, height), title, sf::Style::Default, settings);
    window->setFramerateLimit(60);

    stateMachine = new StateMachine(this);
    inputManager = new InputManager(window, stateMachine);
    font = new sf::Font();

    inputTester = new InputTester(inputManager);

    ResourceLoader loader("resources/");

    loader.loadFont(font, "deathrattlebb_reg.ttf"); // Font source: http://www.1001fonts.com/deathrattle-bb-font.html
    //font = &loader.loadFont("deathrattlebb_reg.ttf");

    inputTester->setTexture(&loader.loadTexture("ball.png"));
}

void Game::start() {
    running = true;

    run();
}

void Game::run() {
    while (window->isOpen() && running) {
        // Returns false when window is close requested
        if (!inputManager->checkForInput()) {
            stop();
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
    inputManager->update();
    stateMachine->update();
}

void Game::draw() {
    window->clear(sf::Color::Black);

    window->draw(*inputTester);
    stateMachine->draw();

    window->display();
}