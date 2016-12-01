#include <iostream>
#include "InputManager.h"
#include "InputObserver.h"
#include "../states/StateMachine.h"

InputManager::InputManager(sf::RenderWindow* window, StateMachine* stateMachine) {
    this->window = window;
    this->stateMachine = stateMachine;

    window->setJoystickThreshold(joystickThreshold);

    setDefaultMappings();
    //initActionStates();
}

InputManager::~InputManager() {
    observers.clear();
}

void InputManager::update(float deltaTime) {

}

void InputManager::setDefaultMappings() {
    actionKeyMappings[Action::MOVE_UP]    = Key::W;
    actionKeyMappings[Action::MOVE_DOWN]  = Key::S;
    actionKeyMappings[Action::MOVE_LEFT]  = Key::A;
    actionKeyMappings[Action::MOVE_RIGHT] = Key::D;
//    actionKeyMappings[Action::USE]        = Key::E;
//    actionKeyMappings[Action::ITEM_1]     = Key::Num1;
//    actionKeyMappings[Action::ITEM_2]     = Key::Num2;
//    actionKeyMappings[Action::ITEM_3]     = Key::Num3;
//    actionKeyMappings[Action::ITEM_4]     = Key::Num4;
//    actionKeyMappings[Action::ITEM_5]     = Key::Num5;
//    actionKeyMappings[Action::ITEM_6]     = Key::Num6;
//    actionKeyMappings[Action::ABILITY_1]  = Key::Num7;
//    actionKeyMappings[Action::ABILITY_2]  = Key::Num8;
//    actionKeyMappings[Action::ABILITY_3]  = Key::Num9;
//    actionKeyMappings[Action::ABILITY_4]  = Key::Num4;

    // Populate the reverse lookup table
    // Key -> sf::Key, value -> Action
    for (auto &actionKey : actionKeyMappings)
        keyActionMappings[actionKey.second] = actionKey.first;
}

void InputManager::initActionStates() {
    actionState[Action::MOVE_UP]          = false;
    actionState[Action::MOVE_DOWN]        = false;
    actionState[Action::MOVE_LEFT]        = false;
    actionState[Action::MOVE_RIGHT]       = false;
}

bool InputManager::checkForInput() {
    sf::Event event;
    bool actionMoveChanged = false;

    while(window->pollEvent(event)) {
        switch(event.type) {
            case sf::Event::Closed:
                return false;

            case sf::Event::KeyPressed: {
                // Set action status(true) if corresponding button is pressed
                for (auto &elem : keyActionMappings) {
                    if (event.key.code == elem.first){
                        actionState[elem.second] = true;
                        actionMoveChanged = true;
                    }
                }

                switch (event.key.code) {
                    case Key::Escape:
                        return false;

                    case Key::Num1:
                        stateMachine->setState(StateMachine::StateID::MAIN_MENU);
                        break;
                    case Key::Num2:
                        stateMachine->setState(StateMachine::StateID::SINGLE_PLAYER);
                        break;
                    case Key::Num3:
                        stateMachine->setState(StateMachine::StateID::MULTI_PLAYER);
                        break;
                    case Key::Num4:
                        stateMachine->setState(StateMachine::StateID::HIGH_SCORE);
                        break;
                    case Key::Num5:
                        stateMachine->setState(StateMachine::StateID::SETTINGS);
                        break;
                }

                break;
            }

            case sf::Event::KeyReleased: {
                if (event.key.code == konamiCode[konamiIndex])
                    konamiIndex++;
                else
                    konamiIndex  = 0;

                if (konamiIndex >= konamiCode.size()){
                    std::cout << "KONAMI CODE UNLEASHED!! AUBY INCOMING!!11!1!|" << std::endl;
                    konamiIndex = 0;
                }

                // Set action status(true) if corresponding button is pressed
                for (auto &elem : keyActionMappings) {
                    if (event.key.code == elem.first) {
                        actionState[elem.second] = false;
                        actionMoveChanged = true;
                    }
                }

                break;
            }

            case sf::Event::MouseButtonPressed: {
                auto mouse = event.mouseButton;
                for (auto &observer : observers)
                    observer->mousePressed(mouse.x, mouse.y, mouse.button);

                break;
            }

            case sf::Event::MouseButtonReleased: {
                break;
            }

            case sf::Event::MouseMoved: {
                auto mouse = event.mouseMove;
                for(auto &observer : observers)
                    observer->mouseMoved(mouse.x, mouse.y);

                break;
            }

            case sf::Event::MouseWheelScrolled: {
                auto mouse = event.mouseWheelScroll;
                for (auto &observer : observers)
                    observer->mouseWheelScrolled(mouse.delta);

                break;
            }

            case sf::Event::JoystickMoved: {
                auto joystick = event.joystickMove;

                if (joystick.axis == sf::Joystick::Axis::R) {
                    if (joystick.position > rTriggerThreshold) {
                        for(auto &observer : observers)
                            observer->actionShoot();
                    }
                }

                break;
            }

            case sf::Event::JoystickButtonPressed:
                break;

            case sf::Event::JoystickButtonReleased:
                break;

            case sf::Event::JoystickConnected:
                // Create function joystickConnected (int id)
                // joystickConnected(event.joystickConnect.joystickId)
                connectedJoysticks++;
                break;

            case sf::Event::JoystickDisconnected:
                // Create function joystickDisconnected (int id)
                // joystickDisconnected(event.joystickConnect.joystickId)
                connectedJoysticks--;
                break;

            case sf::Event::Resized:
                // Window resized -> update map view
                break;

            case sf::Event::LostFocus:
                // Window out of focus -> pause game
                //stateMachine->pause();
                break;

            case sf::Event::GainedFocus:
                // Window gained focus -> resume paused game
                //stateMachine->resume();
                break;

            default:
                break;
        }

        if (actionMoveChanged) {
            for (auto &obs : observers)
                obs->actionMove(checkActionMoveKeys());
        }

        stateMachine->getState()->getDesktop()->HandleEvent(event);
    }

    return true;
}

void InputManager::mapKeyToAction(Action action, Key key) {
    actionKeyMappings[action] = key;
    keyActionMappings[key] = action;
}

void InputManager::addObserver(InputObserver* observer) {
    // Verifies that the observer is not present in the list before adding
    if (!(std::find(observers.begin(), observers.end(), observer) != observers.end()))
        observers.push_back(observer);
}

void InputManager::removeObserver(InputObserver *observer) {
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (*it == observer) {
            observers.erase(it);
        }
    }
}

sf::Vector2f InputManager::checkActionMoveKeys() {
    sf::Vector2f direction = sf::Vector2f(0, 0);

    if (actionState[Action::MOVE_UP])
        direction += sf::Vector2f(0, -1);

    if (actionState[Action::MOVE_DOWN])
        direction += sf::Vector2f(0, 1);

    if (actionState[Action::MOVE_LEFT])
        direction += sf::Vector2f(-1, 0);

    if (actionState[Action::MOVE_RIGHT])
        direction += sf::Vector2f(1, 0);

    return direction;
}

bool InputManager::isJoystickConnected(int joystickID) {
    return playWithJoystick && sf::Joystick::isConnected(joystickID);
}

unsigned int InputManager::connectedJoystickCount() {
    return connectedJoysticks;
}

sf::Vector2f InputManager::getStickPosition(int joystickID, sf::Joystick::Axis xAxis, sf::Joystick::Axis yAxis) {
    if (!isJoystickConnected(joystickID))
        return sf::Vector2f();

    sf::Vector2f direction;

    float x = sf::Joystick::getAxisPosition(0, xAxis);
    float y = sf::Joystick::getAxisPosition(0, yAxis);

    direction.x = x / axisMaxPos;
    direction.y = y / axisMaxPos;

    if (abs(x) > joystickThreshold || abs(y) > joystickThreshold)
        return direction;

    return sf::Vector2f();
}
