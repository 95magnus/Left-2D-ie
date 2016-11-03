//
// Created by Eivind Hystad on 03/11/2016.
//

#ifndef LEFT2DIE_MESSAGEBOX_H
#define LEFT2DIE_MESSAGEBOX_H


#include <string>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics.hpp>
#include "../Game.h"

class MessageBox {
public:
    MessageBox(sf::RenderWindow &window);

    virtual ~MessageBox();

    void draw(std::string msg, int duration, sf::RenderWindow &window);

private:
    bool displayed;
    sf::Clock clock;
    sf::Font font;
    sf::Text message;

    Game* game;
};

#endif //LEFT2DIE_MESSAGEBOX_H
