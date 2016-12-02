#include "StateHighScore.h"

StateHighScore::StateHighScore(Game* game) : StateBase(game) {
    initButtons();
}

StateHighScore::~StateHighScore() {

}

void StateHighScore::pause() {
    desktop->RemoveAll();
}

void StateHighScore::resume() {
    StateBase::resume();
    initButtons();
}


void StateHighScore::update(float deltaTime) {

}

void StateHighScore::initButtons() {
    auto backButton = sfg::Button::Create("Back");
    createButton(backButton, sf::Vector2f(20.0f, 600.0f));
    backButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateHighScore::buttonBackClicked,this));
}

void StateHighScore::draw() {
    sf::Text title("Left[2D]ie", game->getFont(), 140);
    title.setColor(sf::Color::Red);
    title.setPosition(275, 50);

    sf::Text text("High score state", game->getFont());
    text.setColor(sf::Color::Red);
    text.setPosition(300, 300);

    game->getWindow().draw(text);
    game->getWindow().draw(title);
}

void StateHighScore::buttonBackClicked() {
    game->getStateMachine().setState(StateMachine::StateID::MAIN_MENU);
}