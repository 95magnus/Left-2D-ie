//
// Created by Eivind Hystad on 03/11/2016.
//

#include "Message.h"

Message::Message(sf::RenderWindow &window) {
    font.loadFromFile("resources/fonts/PixelOperator8.ttf");
    message.setFont(font);
    message.setColor(sf::Color::White);
    message.setCharacterSize(30);

    // Functions not available on Linux
    //message.setOutlineColor(sf::Color::Black);
    //message.setOutlineThickness(3);

    message.setOrigin(message.getLocalBounds().left / 2, message.getLocalBounds().top);
    displayed = false;

    message.setPosition(550, window.getSize().y - message.getLocalBounds().height - 40);

}

void Message::draw(std::string msg, int duration, sf::RenderWindow &window) {
    if (!displayed) {
        clock.restart();
    }
    displayed = true;
    message.setString(msg);
    if (clock.getElapsedTime().asSeconds() <= duration ) {
        window.draw(message);
    } else {
        return;
    }
}

Message::~Message() {
    /*
    delete displayed;
    delete message;
    delete clock;
    delete font;
     */
}
