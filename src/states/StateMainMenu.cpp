#include "StateMainMenu.h"

StateMainMenu::StateMainMenu(Game* game) : StateBase(game) {

}

StateMainMenu::~StateMainMenu() {

}

void StateMainMenu::update() {

}

void StateMainMenu::draw() {

    sf::Text title("Left[2D]ie", game->getFont(), 100);
    title.setFillColor(sf::Color::Red);
    title.setPosition(200, 50);

    sf::Text text("Main Menu", game->getFont());
    text.setFillColor(sf::Color::Red);
    text.setPosition(300, 300);

    game->getWindow().draw(text);
    game->getWindow().draw(title);
    game->(Button(30,30,"Play"));



    // auto app_window = sfg::Window::Create();
   // game->desktop.Add(app_window);
}

