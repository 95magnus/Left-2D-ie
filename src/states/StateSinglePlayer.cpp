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
    desktop->SetProperty("*", "FontName", "resources/fonts/feast-of-flesh-bb.italic.ttf");
    auto singlePlayerWindow = sfg::Window::Create(sfg::Window::Style::BACKGROUND);
    createSinglePlayerWindow(singlePlayerWindow);

    auto hpBar = sfg::Image::Create();
    createImage(hpBar, "healthbar_border.png");


//    // Widgets
//    auto item1 = sfg::Button::Create("-");
//    createSettingsControlButtons(item1);
//
//    auto item2 = sfg::Button::Create("-");
//    createSettingsControlButtons(item2);
//
//    auto item3 = sfg::Button::Create("-");
//    createSettingsControlButtons(item3);
//
//    auto item4 = sfg::Button::Create();
//    createBoxes(item4);
//
//    auto item5 = sfg::Button::Create();
//    createBoxes(item5);
//
//    auto item6 = sfg::Button::Create();
//    createBoxes(item6);
//
//    auto item7 = sfg::Button::Create();
//    createBoxes(item7);
//
//    auto item8 = sfg::Button::Create();
//    createBoxes(item8);
//
//    auto item9 = sfg::Button::Create();
//    createBoxes(item9);
//
//    auto item0 = sfg::Button::Create();
//    createBoxes(item0);
//
//    auto maintable = sfg::Table::Create();
//
//    auto box = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL );
//    box->SetSpacing(5.f);
//    box->Pack(item1, false);
//    box->Pack(item2, false);
//    box->Pack(item3, false);
//
////    maintable->Attach(item1, sf::Rect<sf::Uint32>(0,0,3,2), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
////    maintable->Attach(item2, sf::Rect<sf::Uint32>(0,2,3,2), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
////    maintable->Attach(item3, sf::Rect<sf::Uint32>(0,6,3,2), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
//
//    auto mainframe = sfg::Frame::Create();
//    mainframe->Add(box);
//    mainframe->SetId("singleplayerframe");
////
////    auto tableAlignment = sfg::Alignment::Create();
////
////    auto alignmentBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
////    alignmentBox->Pack(tableAlignment, true, true);
////
////    tableAlignment->Add(maintable);
////    tableAlignment->SetScale(sf::Vector2f(.0f, .0f));
////    tableAlignment->SetAlignment(sf::Vector2f(.5f, .5f));
////
////    auto soundSettingFrame = sfg::Frame::Create("Music & Sounds");
////    soundSettingFrame->SetId("soundsettingsframe");
////    soundSettingFrame->SetAlignment(sf::Vector2f(.5f, .5f));
////    soundSettingFrame->Add(alignmentBox);
//
//    auto inventoryBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
//    inventoryBox->Pack(mainframe);

    singlePlayerWindow->Add(hpBar);
    desktop->Add(singlePlayerWindow);

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
