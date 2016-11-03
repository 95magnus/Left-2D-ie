#include "StateBase.h"

StateBase::StateBase(Game* game) {
    this->game = game;
    paused = false;
    desktop = new sfg::Desktop();
}

StateBase::~StateBase() {
    delete desktop;
}

void StateBase::updateDesktop() {
    desktop->Update(timer.getElapsedTime().asMilliseconds());
    timer.restart();
}

void StateBase::createButton(sfg::Button::Ptr buttonName, const sf::Vector2f &position) {
    desktop->SetProperty("Button#button", "FontSize", 70.f);

    buttonName->SetId("button");
    buttonName->SetPosition(position);
    buttonName->SetRequisition(sf::Vector2f(0.f, 85.0f));

    desktop->LoadThemeFromFile(themePath);
    desktop->Add(buttonName);
}