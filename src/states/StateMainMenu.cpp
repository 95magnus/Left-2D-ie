#include "StateMainMenu.h"

StateMainMenu::StateMainMenu(Game *game) : StateBase(game) {
    sfgDesktop = &game->getDesktop();

//    playButton = sfg::Button::Create();
//    loadButton(playButton, "PlayButton.png");
//    setButtonPosition(playButton, sf::Vector2f(570.0f, 170.0f));
//
//    hiscoresButton = sfg::Button::Create();
//    loadButton(hiscoresButton, "PlayButton.png");
//    setButtonPosition(hiscoresButton, sf::Vector2f(570.0f, 250.0f));
//
//    settingsButton = sfg::Button::Create();
//    loadButton(settingsButton, "PlayButton.png");
//    setButtonPosition(settingsButton, sf::Vector2f(570.0f, 330.0f));
//
//    quitButton = sfg::Button::Create();
//    loadButton(quitButton, "PlayButton.png");
//    setButtonPosition(quitButton, sf::Vector2f(570.0f, 420.0f));
//
//    std::cout << "Hei" << std::endl;

    playButton = sfg::Button::Create();
    createButton(playButton, sf::Vector2f(570.0f, 250.0f), "PlayButton.png");
}

StateMainMenu::~StateMainMenu() {

}

void StateMainMenu::update() {
//    if(playButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateMainMenu::buttonClicked,this))){
//        game->getStateMachine().setState(StateMachine::StateID::PLAY_GAME);
//    }
}

void StateMainMenu::draw() {
    sf::Text title("Left[2D]ie", game->getFont(), 100);
    title.setFillColor(sf::Color::Red);
    title.setPosition(200, 50);

    game->getWindow().draw(title);
}
//
//void StateMainMenu::loadButton(const sfg::Button::Ptr buttonName, const String &filename) {
//    auto guiImage = new sf::Image();
//    ResourceLoader loader("resources/");
//    loader.loadGuiImage(guiImage, filename);
//    buttonName->SetId(filename);
//}
//
//void StateMainMenu::setButtonPosition(const sfg::Button::Ptr buttonName, const sf::Vector2f &position) {
//    buttonName->SetPosition(position);
//    auto sfgImage = sfg::Image::Create(guiImage);
//    buttonName->SetImage(sfgImage);
//
//    sfgDesktop->Add(buttonName);
//    sfgDesktop->LoadThemeFromFile("resources/gui/theme.css");
//}

void StateMainMenu::buttonClicked() {
    // Get buttons
}

void StateMainMenu::createButton(sfg::Button::Ptr buttonName, const sf::Vector2f &position, const String &filename) {
    auto guiImage = new sf::Image();
    ResourceLoader loader("resources/");
    loader.loadGuiImage(guiImage, filename);
    buttonName->SetId(filename);

    buttonName->SetPosition(position);
    auto sfgImage = sfg::Image::Create(*guiImage);
    buttonName->SetImage(sfgImage);

    sfgDesktop->LoadThemeFromFile("resources/gui/theme.css");
    sfgDesktop->Add(buttonName);
}

