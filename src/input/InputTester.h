#ifndef LEFT2DIE_INPUTTESTER_H
#define LEFT2DIE_INPUTTESTER_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "InputObserver.h"
#include "PlayerController.h"
#include <stdlib.h>
#include <time.h>

class InputManager;

class InputTester : public sf::Drawable, public sf::Transformable, public PlayerController {
public:
    InputTester(InputManager &inputManager);
    virtual ~InputTester() {}

    void update(float deltaTime);
    void setTexture(sf::Texture *texture);

private:
    int radius = 100;
    float movementSpeed = 5.0f;

    //sf::CircleShape shape;
    sf::RectangleShape shape;
    sf::RectangleShape heading;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    //void actionMove(sf::Vector2f direction);
    void actionShoot();
    void mousePressed(int x, int y, sf::Mouse::Button button);

    //void mouseMoved(int x, int y);
    //void joystickMoved(sf::Vector2f direction);

    void setRandomColor();
};

#endif //LEFT2DIE_INPUTTESTER_H
