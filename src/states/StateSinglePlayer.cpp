#include "StateSinglePlayer.h"
#include "../modules/Message.h"
#include "../modules/Player.h"
#include "../modules/Enemy.h"

StateSinglePlayer::StateSinglePlayer(Game* game) : StateBase(game) {
    level = new Level(game->getWindow().getSize(), "testLevel.l2d");
    mb = new Message(game->getWindow());

    window = &game->getWindow();
    view = &level->getView();
    //view->zoom(0.5f);

    //window->setView(*view);
    zombie = new Enemy();
}

StateSinglePlayer::~StateSinglePlayer() {
    delete level;
    delete mb;
    delete player;
    delete zombie;

    window->setView(window->getDefaultView());
}

void StateSinglePlayer::init() {
    player = new Player(game->getWindow(), game->getInputManager());
    players.push_back(player);
}

void StateSinglePlayer::resume() {
    StateBase::resume();
    initGameGui();
}

void StateSinglePlayer::pause() {
    delete score;
    delete coinsContainer;
    delete coins;
    delete hpGreenBar;
    desktop->RemoveAll();
}

void StateSinglePlayer::update(float deltaTime) {
    level->update(deltaTime);
    player->update(deltaTime);
    player->move(deltaTime);

    level->translateMap(player->move(deltaTime));
    //zombie->update(players, deltaTime);
}

void StateSinglePlayer::draw() {
    level->draw(game->getWindow());
    mb->draw("Wave x - Good luck", 8, game->getWindow());
    player->draw(game->getWindow());
    zombie->draw(game->getWindow());
    game->getWindow().draw(*score);
    game->getWindow().draw(*hpGreenBar);
    game->getWindow().draw(*coinsContainer);
    game->getWindow().draw(*coins);
}

void StateSinglePlayer::initGameGui() {
    desktop->SetProperty("*", "FontName", "resources/fonts/feast-of-flesh-bb.italic.ttf");

    font = new sf::Font();
    font->loadFromFile("resources/fonts/feast-of-flesh-bb.italic.ttf");

    // Player bar
    playerBar = sfg::Image::Create();
    createImage(playerBar, "resources/gui/playerbar.png");
    playerBar->SetRequisition(sf::Vector2f(game->getWindowSize()));
    playerBar->SetPosition(sf::Vector2f(10.f, 615.f));

    // Zombie counter label
    zombieLeft = sfg::Label::Create("11");
    createPlayerBarLabel(zombieLeft);
    zombieLeft->SetPosition(sf::Vector2f(125.f, 645.f));

    //// TODO: A counter zombies left

    // Scoreboard
    score = new sf::Text("000000", *font, 60);
    score->setFillColor(sf::Color::White);
    score->setPosition(sf::Vector2f(400.0f, 10.f));
    score->setScale(sf::Vector2f(1.0f, 1.0f));

    //// TODO: Scoreboardsystem

    // Coins
    coinsBar = sfg::Image::Create();
    createImage(coinsBar, "resources/gui/coins.png");
    coinsBar->SetRequisition(sf::Vector2f(game->getWindowSize()));
    coinsBar->SetPosition(sf::Vector2f(800.f, 10.f));

    // Transparent container
    coinsContainer = new sf::RectangleShape(sf::Vector2f(219.0f, 66.f));
    coinsContainer->setFillColor(sf::Color(0,0,0,0));
    coinsContainer->setPosition(799.f, 7.f);

    // Coins counter
    coins = new sf::Text("00000", *font, 40);
    coins->setFillColor(sf::Color::White);
    coins->setPosition(880.f, 15.f);
    coins->setScale(sf::Vector2f(1.0f, 1.0f));

    //// TODO: Coins retrieved after killing zombies

    // Health bar
    hpBar = sfg::Image::Create();
    createImage(hpBar, "resources/gui/healthbar.png");
    hpBar->SetRequisition(sf::Vector2f(game->getWindowSize()));
    hpBar->SetPosition(sf::Vector2f(10.f,10.f));

    // Health
    hpGreenBar = new sf::RectangleShape(sf::Vector2f(154.0f, 16.f));
    hpGreenBar->setFillColor(sf::Color::Green);
    hpGreenBar->setPosition(91.f, 33.f);

    // TODO: Get health input from player

    // Inventory

   // desktop->Add(itemOne);
    desktop->Add(playerBar);
    desktop->Add(zombieLeft);
    desktop->Add(coinsBar);
    desktop->Add(hpBar);
}

void StateSinglePlayer::createImage(sfg::Image::Ptr image, const String &filename) {
    auto temp = new sf::Image;
    if(temp->loadFromFile(filename)){
        image->SetImage(*temp);
    }
}

/// Pause (P)
void StateSinglePlayer::pauseGameGui() {

}

/// Round Clear
void StateSinglePlayer::goToShop() {
    // Timer 5000ms (wait)
    game->getStateMachine().setState(StateMachine::StateID::SHOP);
}

void StateSinglePlayer::onItemOneBoxMarked() {
    // Use item 1
}

void StateSinglePlayer::onItemTwoBoxMarked() {
    // Use item 2
}

void StateSinglePlayer::onItemThreeBoxMarked() {
    // Use item 3
}

void StateSinglePlayer::onItemFourBoxMarked() {
    // Use item 4
}

void StateSinglePlayer::onItemFiveBoxMarked() {
    // Use item 5
}

void StateSinglePlayer::onItemSixBoxMarked() {
    // Use item 6
}

void StateSinglePlayer::onAbilityOneBoxMarked() {
    // Use ability 1
}

void StateSinglePlayer::onAbilityTwoBoxMarked() {
    // Use ability 2
}

void StateSinglePlayer::onAbilityThreeBoxMarked() {
    // Use ability 3
}

void StateSinglePlayer::onAbilityFourBoxMarked() {
    // Use ability 4
}
