//
// Created by Eivind Hystad on 03/11/2016.
//

#include "MessageBox.h"

MessageBox::MessageBox(sf::RenderWindow &window) {
    font.loadFromFile("resources/fonts/PixelOperator8.ttf");
    message.setFont(font);
    message.setFillColor(sf::Color::White);
    message.setCharacterSize(30);
    message.setOutlineColor(sf::Color::Black);
    message.setOutlineThickness(3);
    message.setOrigin(message.getLocalBounds().left / 2, message.getLocalBounds().top);
    displayed = false;

    message.setPosition(window.getSize().x / 2 - message.getLocalBounds().width / 2, window.getSize().y - message.getLocalBounds().height - 40);

}

void MessageBox::draw(std::string msg, int duration, sf::RenderWindow &window) {
    if (!displayed) {
        clock.restart();
    }

    displayed = true;
    message.setString(msg);

    /*TODO: the line below needs to be in the messageboxs constructor
      TODO: this is a temporary solution, it shouldnt have to set the position with each iteration
     */
    //message.setPosition(window.getSize().x / 2 - message.getLocalBounds().width / 2, window.getSize().y - message.getLocalBounds().height - 10);

    if (clock.getElapsedTime().asSeconds() <= duration ) {
        window.draw(message);
    } else {
        return;
    }
}

MessageBox::~MessageBox() {
    /*
    delete displayed;
    delete message;
    delete clock;
    delete font;
     */
}
