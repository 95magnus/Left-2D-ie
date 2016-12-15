#include "StateMachine.h"

StateMachine::StateMachine(Game* game) {
    this->game = game;

    states[StateID::MAIN_MENU] = new StateMainMenu(game);
    states[StateID::PLAY_GAME] = new StatePlayGame(game);
    states[StateID::SINGLE_PLAYER] = new StateSinglePlayer(game);
    states[StateID::MULTI_PLAYER] = new StateMultiPlayer(game);
    states[StateID::HIGH_SCORE] = new StateHighScore(game);
    states[StateID::SETTINGS] = new StateSettings(game);
    states[StateID::SHOP] = new StateShop(game);

    currentState = states[StateID::MAIN_MENU];

    paused = false;
}

StateMachine::~StateMachine() {
    for (auto& s : states){
        delete s.second;
    }
}

void StateMachine::initStates() {
    for (auto &state : states)
        state.second->init();
}

void StateMachine::update(float deltaTime) {
    currentState->update(deltaTime);
    currentState->updateDesktop();
}

void StateMachine::draw(sf::RenderWindow &window) {
    currentState->draw(window);
}

void StateMachine::pause() {
    if (!paused){
        currentState->pause();
        paused = true;
    }
}

void StateMachine::resume() {
    if (paused) {
        currentState->resume();
        paused = false;
    }
}

void StateMachine::setState(StateID state) {
    currentState->pause();
    currentState = states[state];
    currentState->resume();
}

StateBase *StateMachine::getState(StateMachine::StateID state) {
    return states[state];
}
