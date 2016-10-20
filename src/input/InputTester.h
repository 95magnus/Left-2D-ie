#ifndef LEFT2DIE_INPUTTESTER_H
#define LEFT2DIE_INPUTTESTER_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "InputObserver.h"

class InputManager;

class InputTester : public sf::Drawable, public sf::Transformable, public InputObserver {
public:
    InputTester(InputManager* inputManager);
    virtual ~InputTester() {}

    void setTexture(sf::Texture *texture);

private:
    int radius = 30;
    float movementSpeed = 7.0f;

    sf::Vector2f mousePos;
    int headingAngle;

    sf::CircleShape shape;
    sf::RectangleShape heading;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void actionMove(sf::Vector2f direction);
    void mousePressed(int x, int y, sf::Mouse::Button button);
    void mouseMoved(int x, int y);
};

#endif //LEFT2DIE_INPUTTESTER_H
