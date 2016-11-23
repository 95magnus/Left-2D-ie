#ifndef LEFT2DIE_INPUTOBSERVER_H
#define LEFT2DIE_INPUTOBSERVER_H

#include <SFML/System.hpp>
#include <SFML/Window/Mouse.hpp>

class InputManager;

class InputObserver {
public:
    InputObserver(InputManager* inputManager);
    virtual ~InputObserver() {}

    virtual void actionMove(sf::Vector2f direction) {}
    virtual void actionShoot() {}
    virtual void actionUse() {}

    virtual void mousePressed(int x, int y, sf::Mouse::Button button) {}
    virtual void mouseMoved(int x, int y) {}
    virtual void mouseWheelScrolled(float delta) {}

    virtual void joystickMoved(sf::Vector2f direction) {}

protected:
    InputManager* inputManager;
};


#endif //LEFT2DIE_INPUTOBSERVER_H
