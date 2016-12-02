#include "StatePlayGame.h"

StatePlayGame::StatePlayGame(Game *game) : StateBase(game) {
    initButtons();
}

StatePlayGame::~StatePlayGame() {

}
void StatePlayGame::update(float deltaTime) {

}

void StatePlayGame::pause() {
    desktop->RemoveAll();
}

void StatePlayGame::resume() {
    StateBase::resume();
    initButtons();
}

void StatePlayGame::initButtons() {
    auto singlePlayerButton = sfg::Button::Create("Single Player");
    createButton(singlePlayerButton, sf::Vector2f(550.0f, 280.0f));
    singlePlayerButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StatePlayGame::buttonSinglePlayerClicked,this));

    auto multiplayerButton = sfg::Button::Create("Multiplayer");
    createButton(multiplayerButton, sf::Vector2f(550.0f, 370.0f));
    multiplayerButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StatePlayGame::buttonMultiplayerClicked,this));

    auto backButton = sfg::Button::Create("Back");
    createButton(backButton, sf::Vector2f(20.0f, 600.0f));
    backButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StatePlayGame::buttonBackClicked,this));
}

void StatePlayGame::draw() {
    sf::Text title("Left[2D]ie", game->getFont(), 140);
    title.setColor(sf::Color::Red);
    title.setPosition(275, 50);

    game->getWindow().draw(title);
}

void StatePlayGame::buttonSinglePlayerClicked() {
    game->getStateMachine().setState(StateMachine::StateID::SINGLE_PLAYER);
}

void StatePlayGame::buttonMultiplayerClicked() {
    game->getStateMachine().setState(StateMachine::StateID::MULTI_PLAYER);
}

void StatePlayGame::buttonBackClicked() {
    game->getStateMachine().setState(StateMachine::StateID::MAIN_MENU);

}