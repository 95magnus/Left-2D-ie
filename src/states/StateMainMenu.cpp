#include "StateMainMenu.h"

StateMainMenu::StateMainMenu(Game *game) : StateBase(game) {

    game->getStateMachine();
}

StateMainMenu::~StateMainMenu() {
    delete guiImage;
}

void StateMainMenu::update() {
    if(playButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateMainMenu::buttonClicked,this))){
        game->getStateMachine().setState(StateMachine::StateID::PLAY_GAME);
    }
}

void StateMainMenu::draw() {
    sf::Text title("Left[2D]ie", game->getFont(), 100);
    title.setFillColor(sf::Color::Red);
    title.setPosition(200, 50);

    sf::Text text("Main Menu", game->getFont());
    text.setFillColor(sf::Color::Red);
    text.setPosition(300, 300);

    game->getWindow().draw(text);
    game->getWindow().draw(title);

    std::cout << "Lalala" << std::endl;

    playButton = sfg::Button::Create();
    loadButton(playButton, "PlayButton.png");
    setButtonPosition(playButton, sf::Vector2f(570.0f, 170.0f));

    hiscoresButton = sfg::Button::Create();
    loadButton(hiscoresButton, "PlayButton.png");
    setButtonPosition(hiscoresButton, sf::Vector2f(570.0f, 250.0f));

    settingsButton = sfg::Button::Create();
    loadButton(settingsButton, "PlayButton.png");
    setButtonPosition(settingsButton, sf::Vector2f(570.0f, 330.0f));

    quitButton = sfg::Button::Create();
    loadButton(quitButton, "PlayButton.png");
    setButtonPosition(quitButton, sf::Vector2f(570.0f, 420.0f));
}

void StateMainMenu::loadButton(const sfg::Button::Ptr buttonName, const String &filename) {
    this->buttonName = buttonName;
    this->filename = filename;

    guiImage = new sf::Image();
    ResourceLoader loader("resources/");
    loader.loadGuiImage(guiImage, filename);
    buttonName->SetId(filename);
}

void StateMainMenu::setButtonPosition(const sfg::Button::Ptr buttonName, const sf::Vector2f &position) {
    this->buttonName = buttonName;
    this->position = position;

    buttonName->SetPosition(position);
    sfgImage = sfg::Image::Create(*guiImage);
    buttonName->SetImage(sfgImage);


    game->sfgDesktop.LoadThemeFromFile("resources/gui/theme.css");
    game->sfgDesktop.Add(buttonName);
}

void StateMainMenu::buttonClicked() {
    // Get buttons


}

