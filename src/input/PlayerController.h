#ifndef LEFT2DIE_PLAYERCONTROLLER_H
#define LEFT2DIE_PLAYERCONTROLLER_H

#include "InputObserver.h"
#include "InputManager.h"

class PlayerController : public InputObserver {
public:
    PlayerController(InputManager &inputManager);
    PlayerController(InputManager &inputManager, int joystickID);
    virtual ~PlayerController();

    virtual void update(float deltaTime);

    virtual void actionMove(sf::Vector2f direction);
    virtual void actionShoot() {}
    virtual void mousePressed(int x, int y, sf::Mouse::Button button) {}

    void pollJoystick();
    void setJoystickID(int joystickID);

private:
    int joystickID = -1;
protected:
    bool usingController = false;

    sf::Vector2f moveDirection;
    sf::Vector2f viewingDirection;
    bool shooting;
};


#endif //LEFT2DIE_PLAYERCONTROLLER_H
