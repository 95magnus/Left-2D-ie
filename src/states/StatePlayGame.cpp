#include "StatePlayGame.h"

StatePlayGame::StatePlayGame(Game *game) : StateBase(game) {
    initButtons();
}

StatePlayGame::~StatePlayGame() {

}

void StatePlayGame::pause() {
    desktop->RemoveAll();
}

void StatePlayGame::resume() {
    StateBase::resume();
    initButtons();
}

void StatePlayGame::update() {

}

void StatePlayGame::initButtons() {
    // Some weird reason the first button don't match with sfgDesktop in x-axis: making an invisible button
    auto invisibleButton = sfg::Button::Create("");
    createButton(invisibleButton, sf::Vector2f(0.f, 0.f));

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
    title.setFillColor(sf::Color::Red);
    title.setPosition(275, 50);

//    sf::Text text("Play", game->getFont());
//    text.setFillColor(sf::Color::Red);
//    text.setPosition(300, 300);
//
//    game->getWindow().draw(text);
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