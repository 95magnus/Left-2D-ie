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

private:
    int radius = 30;
    float movementSpeed = 7.0f;

    sf::CircleShape shape;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void actionMove(sf::Vector2f direction);

    void mousePressed(int x, int y, sf::Mouse::Button button);
};

#endif //LEFT2DIE_INPUTTESTER_H
