
#include "InputTester.h"
#include "InputManager.h"

InputTester::InputTester(InputManager &inputManager) : PlayerController(inputManager) {
    shape = sf::RectangleShape(sf::Vector2f(150, 75));
    shape.setFillColor(sf::Color::Green);
    //shape.setOrigin(radius, radius);
    shape.setOrigin(shape.getSize().x/2, shape.getSize().y/2);

    heading = sf::RectangleShape(sf::Vector2f(radius, 2));
    heading.setFillColor(sf::Color::Blue);
    heading.setOrigin(0, 0);

    srand(time(NULL));
}

void InputTester::update(float deltaTime) {
    PlayerController::update(deltaTime);

    shape.move(moveDirection * movementSpeed);
    heading.move(moveDirection * movementSpeed);

    setOrigin(getPosition());
}

void InputTester::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    target.draw(shape, states);
    //target.draw(heading, states);
}

void InputTester::actionShoot() {
    printf("Pew pew pew\n");

    setRandomColor();
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

/*
void InputTester::actionMove(sf::Vector2f direction) {
    moveDirection = direction;
}
 */


void InputTester::setTexture(sf::Texture *texture) {
    texture->setSmooth(true);
    shape.setTexture(texture);
}

void InputTester::setRandomColor() {
    int r = rand() % 255;
    int g = rand() % 255;
    int b = rand() % 255;

    shape.setFillColor(sf::Color(r, g, b));
}
