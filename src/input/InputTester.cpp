#include "InputTester.h"
#include "InputManager.h"

InputTester::InputTester(InputManager* inputManager) : InputObserver(inputManager) {
    shape = sf::CircleShape(radius);
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin(radius/2, radius/2);

    srand(time(NULL));
}

void InputTester::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    target.draw(shape, states);
}

void InputTester::mousePressed(int x, int y, sf::Mouse::Button button) {
    if (button == sf::Mouse::Button::Left) {
        shape.setPosition(x, y);
    } else if (button == sf::Mouse::Button::Right) {
        int r = rand() % 255;
        int g = rand() % 255;
        int b = rand() % 255;

        shape.setFillColor(sf::Color(r, g, b));
    }
}

void InputTester::actionMove(sf::Vector2f direction) {
    shape.move(direction * movementSpeed);
}
