#include "StateSinglePlayer.h"

StateSinglePlayer::StateSinglePlayer(Game* game) : StateBase(game) {
    initGameGui();
}

StateSinglePlayer::~StateSinglePlayer() {

}

void StateSinglePlayer::resume() {
    StateBase::resume();
    initGameGui();
}

void StateSinglePlayer::pause() {
    desktop->RemoveAll();
}

void StateSinglePlayer::update() {

}

void StateSinglePlayer::draw() {
    sf::Text title("Left[2D]ie", game->getFont(), 140);
    title.setFillColor(sf::Color::Red);
    title.setPosition(275, 50);

    sf::Text text("Single player state", game->getFont());
    text.setFillColor(sf::Color::Red);
    text.setPosition(300, 300);

    game->getWindow().draw(text);
    game->getWindow().draw(title);
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
