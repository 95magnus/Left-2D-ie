#include "Button.h"

Button::Button(sfg::Button::Ptr button) {

}

Button::~Button() {

}

void Button::update() {

}

void Button::draw(sfg::Button::Ptr buttonName, const sf::Vector2f &position) {
    desktop = stateBase->getDesktop();
    desktop->SetProperty("Button#button", "FontSize", 70.f);

    buttonName->SetId("button");
    buttonName->SetPosition(position);
    buttonName->SetRequisition(sf::Vector2f(0.f, 85.0f));

    desktop->LoadThemeFromFile("resources/gui/theme.css");
    desktop->Add(buttonName);
}
