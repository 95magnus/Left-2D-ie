#include "StateMainMenu.h"

StateMainMenu::StateMainMenu(Game *game) : StateBase(game) {
    //sfgDesktop = &game->getDesktop();

    // Some weird reason the first button don't match with sfgDesktop in x-axis: making an invisible button
    auto invisibleButton = sfg::Button::Create("");
    createButton(invisibleButton, sf::Vector2f(0.f, 0.f));

    auto playButton = sfg::Button::Create("Play");
    createButton(playButton, sf::Vector2f(670.0f, 240.0f));
    playButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateMainMenu::buttonPlayClicked,this));

    auto hiscoresButton = sfg::Button::Create("Hiscores");
    createButton(hiscoresButton, sf::Vector2f(670.0f, 330.0f));
    hiscoresButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateMainMenu::buttonHiscoresClicked,this));

    auto settingsButton = sfg::Button::Create("Settings");
    createButton(settingsButton, sf::Vector2f(670.0f, 420.0f));
    settingsButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateMainMenu::buttonSettingsClicked,this));

    auto quitButton = sfg::Button::Create("Quit");
    createButton(quitButton, sf::Vector2f(670.0f, 510.0f));
    quitButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateMainMenu::buttonQuitClicked,this));
}

StateMainMenu::~StateMainMenu() {

}

void StateMainMenu::update() {
    desktop->Refresh();
}

void StateMainMenu::draw() {
    sf::Text title("Left[2D]ie", game->getFont(), 140);
    title.setFillColor(sf::Color::Red);
    title.setPosition(275, 50);

    sf::Text text("Main Menu state", game->getFont());
    text.setFillColor(sf::Color::Red);
    text.setPosition(300, 300);

    game->getWindow().draw(text);
    game->getWindow().draw(title);
}

void StateMainMenu::createButton(sfg::Button::Ptr buttonName, const sf::Vector2f &position) {
    desktop->SetProperty("Button#button", "FontSize", 70.f);

    buttonName->SetId("button");
    buttonName->SetPosition(position);
    buttonName->SetRequisition(sf::Vector2f(0.f, 85.0f));

    desktop->LoadThemeFromFile("resources/gui/theme.css");
    desktop->Add(buttonName);
}

void StateMainMenu::buttonPlayClicked() {
    desktop->RemoveAll();
    game->getStateMachine().setState(StateMachine::StateID::PLAY_GAME);
}

void StateMainMenu::buttonHiscoresClicked() {
    desktop->RemoveAll();
    game->getStateMachine().setState(StateMachine::StateID::HIGH_SCORE);
}

void StateMainMenu::buttonSettingsClicked() {
    desktop->RemoveAll();
    game->getStateMachine().setState(StateMachine::StateID::SETTINGS);
}

void StateMainMenu::buttonQuitClicked() {
    desktop->RemoveAll();
    game->stop();
}

//void StateMainMenu::setButtonColor(const String &s, const sf::Color &color, const sf::Color &prelight) {
//
//}

