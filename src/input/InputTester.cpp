#include "InputTester.h"
#include "InputManager.h"
#include "../util/VectorUtil.h"

InputTester::InputTester(InputManager* inputManager) : InputObserver(inputManager) {
    shape = sf::CircleShape(radius);
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin(radius, radius);

    heading = sf::RectangleShape(sf::Vector2f(radius, 2));
    heading.setFillColor(sf::Color::Blue);
    heading.setOrigin(0, 0);

    srand(time(NULL));
}

void InputTester::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    target.draw(shape, states);
    target.draw(heading, states);
}

void InputTester::mousePressed(int x, int y, sf::Mouse::Button button) {
    if (button == sf::Mouse::Button::Left) {
        shape.setPosition(x, y);
        heading.setPosition(x, y);
    } else if (button == sf::Mouse::Button::Right) {
        int r = rand() % 255;
        int g = rand() % 255;
        int b = rand() % 255;

        shape.setFillColor(sf::Color(r, g, b));
    }
}

void InputTester::mouseMoved(int x, int y) {
    mousePos = sf::Vector2f(x, y);
    auto test = shape.getOrigin();
    headingAngle = 30;

    shape.setRotation(headingAngle);
    heading.setRotation(headingAngle);

    printf("Mouse(%d, %d) | Pos(%d, %d) -> Angle: %d\n",
           x, y, test.x, test.y,
           util::angleDegrees(test, mousePos)
    );
}

void InputTester::actionMove(sf::Vector2f direction) {
    shape.move(direction * movementSpeed);
    heading.move(direction * movementSpeed);

    setOrigin(getPosition());
}

void InputTester::setTexture(sf::Texture *texture) {
    texture->setSmooth(true);
    shape.setTexture(texture);
}
