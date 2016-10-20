#include "StateMainMenu.h"
#include <SFML/Graphics.hpp>


StateMainMenu::StateMainMenu(Game* game) : StateBase(game) {

}

StateMainMenu::~StateMainMenu() {

}

void StateMainMenu::update() {

}

void StateMainMenu::draw() {
    sf::Text title("Left[2D]ie", game->getFont(), 100);
    title.setColor(sf::Color::Red);
    title.setPosition(200, 50);

    sf::Text text("Play", game->getFont());
    text.setColor(sf::Color::Red);
    text.setPosition(600, 200);

    game->getWindow().draw(text);
    game->getWindow().draw(title);

    //auto app_window = sfg::Window::Create();
    //game->desktop.Add(app_window);
}

