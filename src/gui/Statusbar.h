//
// Created by Eivind Hystad on 25/11/2016.
//

#ifndef LEFT2DIE_STATUSBAR_H
#define LEFT2DIE_STATUSBAR_H


#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../entites/Player.h"

class Statusbar {
public:
    virtual ~Statusbar();
    Statusbar();
    void draw(sf::RenderWindow &window, Player *player);

private:
    sf::Text text;
    sf::Font font;
    sf::Text health;
    sf::Texture heartImg;
    sf::Texture scoreImg;
    sf::RectangleShape heart;
    sf::RectangleShape medal;
    sf::Text score;
    sf::Text wave;
    int borderMargin;
};


#endif //LEFT2DIE_STATUSBAR_H
