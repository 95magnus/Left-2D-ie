//
// Created by Eivind Hystad on 25/11/2016.
//

#include "Statusbar.h"

Statusbar::Statusbar() {
    if (!font.loadFromFile("resources/fonts/PixelOperator8.ttf")) {
        printf("Couldn't load font.");
    }
    if (!heartImg.loadFromFile("resources/textures/spritesheets/heart1.png")) {
        printf("Couldn't load image.");
    }
    /*if (!scoreImg.loadFromFile("resources/textures/spritesheets/medal.png")) {
        printf("Couldn't load image.");
    }*/
    text.setFont(font);
    text.setCharacterSize(20);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(2);
    heart.setTexture(&heartImg);
    //medal.setTexture(&scoreImg);
    heart.setSize(sf::Vector2f(20, 20));
    //medal.setSize(sf::Vector2f(12, 20));
    borderMargin = 5;
    score = text;
    wave = text;
    health = text;
}

Statusbar::~Statusbar() {

}

void Statusbar::draw(sf::RenderWindow &window, Player *player) {
    health.setString("Health: " + std::to_string(player->getHealth()));
    score.setString("$ Score: " + std::to_string(player->getScore()));
    wave.setString("Wave: 1");
    heart.setPosition(0 + borderMargin, 0 + borderMargin);
    health.setPosition(0 + borderMargin, 0 + borderMargin);
    //medal.setPosition(window.getSize().x - borderMargin*2 - score.getLocalBounds().width - medal.getSize().x, 0 + borderMargin);
    score.setPosition(window.getSize().x - score.getLocalBounds().width - borderMargin, 0 + borderMargin);
    wave.setPosition(window.getSize().x - wave.getLocalBounds().width - borderMargin, window.getSize().y - wave.getLocalBounds().height - borderMargin);
    window.draw(medal);
    window.draw(heart);
    window.draw(health);
    window.draw(score);
    window.draw(wave);
}