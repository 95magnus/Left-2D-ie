#include "StateMainMenu.h"

StateMainMenu::StateMainMenu(Game *game) : StateBase(game) {
    initButtons();

    ResourceLoader loader("resources/");
    backgroundImage = new sf::Texture();
    loader.loadTexture(backgroundImage, "background.png");
    background.setTexture(backgroundImage);
    background.setSize(game->getWindowSize());
}

StateMainMenu::~StateMainMenu() {

}

void StateMainMenu::update(float deltaTime) {

}

void StateMainMenu::draw(sf::RenderWindow &window) {
    sf::Text title("Left[2D]ie", game->getFont(), 140);

    // sf::Text does not contain setFillColor() on Linux?
    //title.setFillColor(sf::Color::Red);
    title.setColor(sf::Color::Red);
    title.setPosition(275, 50);

    game->getWindow().draw(background);
    game->getWindow().draw(title);
}

void StateMainMenu::resume() {
    StateBase::resume();
    initButtons();
}

void StateMainMenu::pause() {
    desktop->RemoveAll();
}

void StateMainMenu::initButtons() {
    desktop->SetProperty("*", "FontName", "resources/fonts/feast-of-flesh-bb.italic.ttf");

    auto playButton = sfg::Button::Create("Play");
    createButton(playButton, sf::Vector2f(670.0f, 240.0f));

    auto hiscoresButton = sfg::Button::Create("Hiscores");
    createButton(hiscoresButton, sf::Vector2f(670.0f, 330.0f));

    auto settingsButton = sfg::Button::Create("Settings");
    createButton(settingsButton, sf::Vector2f(670.0f, 420.0f));

    auto quitButton = sfg::Button::Create("Quit");
    createButton(quitButton, sf::Vector2f(670.0f, 510.0f));

    // Signals
    playButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateMainMenu::buttonPlayClicked,this));
    hiscoresButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateMainMenu::buttonHiscoresClicked,this));
    settingsButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateMainMenu::buttonSettingsClicked,this));
    quitButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateMainMenu::buttonQuitClicked,this));
}

void StateMainMenu::buttonPlayClicked() {
    game->getStateMachine().setState(StateMachine::StateID::PLAY_GAME);
}

void StateMainMenu::buttonHiscoresClicked() {
    game->getStateMachine().setState(StateMachine::StateID::HIGH_SCORE);
}

void StateMainMenu::buttonSettingsClicked() {
    game->getStateMachine().setState(StateMachine::StateID::SETTINGS);
}

void StateMainMenu::buttonQuitClicked() {
    game->stop();
}

