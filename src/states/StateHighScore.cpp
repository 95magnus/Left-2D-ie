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
    // Some weird reason the first button don't match with sfgDesktop in x-axis: making an invisible button
    auto invisibleButton = sfg::Button::Create("");
    createButton(invisibleButton, sf::Vector2f(0.f, 0.f));

    auto backButton = sfg::Button::Create("Back");
    createButton(backButton, sf::Vector2f(20.0f, 600.0f));
    backButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateHighScore::buttonBackClicked,this));
}

void StateHighScore::draw(sf::RenderWindow &window) {
    sf::Text title("Left[2D]ie", game->getFont(), 140);
    title.setColor(sf::Color::Red);
    title.setPosition(275, 50);

    sf::Text text("High score state", game->getFont());
    text.setColor(sf::Color::Red);
    text.setPosition(300, 300);

    window.draw(text);
    window.draw(title);
}

void StateHighScore::buttonBackClicked() {
    game->getStateMachine().setState(StateMachine::StateID::MAIN_MENU);
}


//
//void
//StatePlayGame::createImageButton(sfg::Button::Ptr buttonName, const sf::Vector2f &position, const String &filename) {
//    desktop->SetProperty("Button#button", "FontSize", 70.f);
//
//    auto guiImage = new sf::Image();
//    ResourceLoader loader("resources/");
//    loader.loadGuiImage(guiImage, filename);
//
//    buttonName->SetId(filename);
//    buttonName->SetPosition(position);
//    buttonName->SetRequisition(sf::Vector2f(0.f, 85.0f));
//
//    auto sfgImage = sfg::Image::Create(*guiImage);
//    buttonName->SetImage(sfgImage);
//
//    desktop->LoadThemeFromFile("resources/gui/theme.css");
//    desktop->Add(buttonName);
//}
