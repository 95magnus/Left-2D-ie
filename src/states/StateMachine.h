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
        SETTINGS
    };

    StateMachine(Game* game);
    virtual ~StateMachine();

    void update();
    void draw();

    void pause();
    void resume();

    void setState(StateID state);
    StateBase* getState() const { return currentState; }

    void togglePause() { paused = !paused; }

protected:
    Game* game;

    bool paused;

    StateBase* currentState;
    std::map<StateID, StateBase*> states;
};

#endif //LEFT2DIE_STATEMACHINE_H
