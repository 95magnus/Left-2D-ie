#ifndef LEFT2DIE_INPUTMANAGER_H
#define LEFT2DIE_INPUTMANAGER_H

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <map>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFGUI/Widgets.hpp>


class InputObserver;
class StateMachine;

typedef sf::Keyboard::Key Key;

class InputManager {
public:
    enum class Action {
        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,
        USE,
        ITEM_1,
        ITEM_2,
        ABILITY_1,
    };

    InputManager(sf::RenderWindow* window);
    virtual ~InputManager();

    void update(float deltaTime);

    bool checkForInput();
    void setDefaultMappings();
    void initActionStates();
    void mapKeyToAction(Action action, Key key);

    sf::Vector2f checkActionMoveKeys();

    bool isWindowFocused();

    bool isJoystickConnected(int joystickID);
    unsigned int connectedJoystickCount();
    sf::Vector2f getStickPosition(int joystickID, sf::Joystick::Axis xAxis, sf::Joystick::Axis yAxis);
    bool isTriggerPressed(int joystickID, sf::Joystick::Axis trigger);

    void setStateMachine(StateMachine *stateMachine);

    void addObserver(InputObserver* observer);
    void removeObserver(InputObserver* observer);

protected:
    std::vector<Key> konamiCode = {
            Key::Up,
            Key::Up,
            Key::Down,
            Key::Down,
            Key::Left,
            Key::Right,
            Key::Left,
            Key::Right,
            Key::B,
            Key::A,
            Key::Return
    };

    int konamiIndex = 0;

    bool playWithJoystick = false, windowFocus = false;

    const float joystickThreshold = 15.0f, triggerTreshold = 15.0f, axisMaxPos = 100.0f;
    unsigned int connectedJoysticks = 0;

    std::vector<InputObserver*> observers;

    std::map<Action, Key> actionKeyMappings;
    std::map<Key, Action> keyActionMappings;
    std::map<Action, bool> actionState;

    sf::RenderWindow *window;
    StateMachine* stateMachine;
};

#endif //LEFT2DIE_INPUTMANAGER_H
