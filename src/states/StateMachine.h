#ifndef LEFT2DIE_STATEMACHINE_H
#define LEFT2DIE_STATEMACHINE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <map>
#include "../Game.h"
#include "StateMainMenu.h"
#include "StatePlayGame.h"
#include "StateSinglePlayer.h"
#include "StateMultiPlayer.h"
#include "StateHighScore.h"
#include "StateSettings.h"
#include "StateShop.h"

class Game;
class StateBase;

class StateMachine {
public:
    enum class StateID {
        MAIN_MENU,
        PLAY_GAME,
        SINGLE_PLAYER,
        MULTI_PLAYER,
        HIGH_SCORE,
        SETTINGS,
        SHOP
    };

    StateMachine(Game* game);
    virtual ~StateMachine();

    void initStates();

    void update(float deltaTime);
    void draw(sf::RenderWindow &window);

    void pause();
    void resume();

    void setState(StateID state);
    StateBase* getState() const { return currentState; }

    StateBase* getState(StateID state);

    void togglePause() { paused = !paused; }

protected:
    Game* game;

    bool paused;

    StateBase* currentState;
    std::map<StateID, StateBase*> states;
};

#endif //LEFT2DIE_STATEMACHINE_H
