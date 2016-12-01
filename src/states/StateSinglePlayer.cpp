#include "StateSinglePlayer.h"
#include "../modules/Message.h"
#include "../modules/Player.h"
#include "../modules/Enemy.h"

StateSinglePlayer::StateSinglePlayer(Game* game) : StateBase(game) {
    //initGameGui();
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
}

void StateSinglePlayer::initGameGui() {
    // Main game window
//    desktop->SetProperty("*", "FontName", "resources/fonts/feast-of-flesh-bb.italic.ttf");
//    auto singlePlayerWindow = sfg::Window::Create(sfg::Window::Style::BACKGROUND);
//    createSinglePlayerWindow(singlePlayerWindow);
//
//    auto hpBar = sfg::Image::Create();
//    createImage(hpBar, "healthbar_border.png");

//
//    singlePlayerWindow->Add(hpBar);
//    desktop->Add(singlePlayerWindow);

}

void StateSinglePlayer::pauseGameGui() {

}

void StateSinglePlayer::goToShop() {

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
