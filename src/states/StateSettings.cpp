#include "StateSettings.h"

StateSettings::StateSettings(Game* game) : StateBase(game) {
    initGui();
}

StateSettings::~StateSettings() {

}

void StateSettings::pause() {
    desktop->RemoveAll();
}

void StateSettings::resume() {
    StateBase::resume();
    initGui();
}

void StateSettings::update() {

}

void StateSettings::initGui() {
    auto settingsWindow = sfg::Window::Create(sfg::Window::Style::BACKGROUND);
    createSettingsWindow(settingsWindow, sf::Vector2f(222.0f, 210.0f));

    auto separator = sfg::Separator::Create( sfg::Separator::Orientation::HORIZONTAL);

    // 0 pixel spacing
    auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);

    auto settingsLabel = sfg::Label::Create("Settings");
    createLabel(settingsLabel);

    auto doneButton = sfg::Button::Create("Done");
    createSettingsButton(doneButton);

    auto fixed = sfg::Fixed::Create();

    fixed->Put(doneButton, sf::Vector2f(10.f, 400.f));
    box->Pack(fixed);

////    auto mainTable = sfg::Table::Create();
//    auto semiTable = sfg::Table::Create();
//    auto buttonTable = sfg::Table::Create();
////
////    auto backButton = sfg::Button::Create("Back");
////    createButton(backButton, sf::Vector2f(20.0f, 600.0f));
////    backButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::buttonBackClicked,this));
//
//    auto invisibleButton = sfg::Button::Create("");
//    auto invisibleButtonAlignment = sfg::Alignment::Create();
//    createSettingsButton(invisibleButton, invisibleButtonAlignment);
//
//    auto muteMusicButton = sfg::CheckButton::Create("Disable music");
//    auto muteMusicButtonAlignment = sfg::Alignment::Create();
//    createSettingsGuiButton(muteMusicButton, muteMusicButtonAlignment);
//    muteMusicButton->GetSignal(sfg::CheckButton::OnToggle).Connect(std::bind(&StateSettings::buttonMuteMusicClicked, this));
//
//    auto muteSoundButton = sfg::CheckButton::Create("Disable sound");
//    auto muteSoundButtonAlignment = sfg::Alignment::Create();
//    createSettingsGuiButton(muteSoundButton, muteSoundButtonAlignment);
//    muteSoundButton->GetSignal(sfg::CheckButton::OnToggle).Connect(std::bind(&StateSettings::buttonMuteSoundClicked, this));
//
////    auto applyButton = sfg::Button::Create("Apply");
////    auto applyButtonAlignment = sfg::Alignment::Create();
////    createSettingsButton(applyButton, applyButtonAlignment);
////    applyButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::buttonApplyClicked,this));
////
////    auto defaultButton = sfg::Button::Create("Restore default");
////    auto defaultButtonAlignment = sfg::Alignment::Create();
////    createSettingsButton(defaultButton, defaultButtonAlignment);
////    defaultButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::buttonDefaultClicked,this));
//
//    /* item buttons */
////    auto itemOneButton = sfg::Button::Create();
////    auto itemOneButtonAlignment = sfg::Alignment::Create();
////    createImageButton(itemOneButton, "  1  ",itemOneButtonAlignment);
////
////    auto itemTwoButton = sfg::Button::Create();
////    auto itemTwoButtonAlignment = sfg::Alignment::Create();
////    createImageButton(itemTwoButton, "  2  ",itemTwoButtonAlignment);
////
////    auto itemThreeButton = sfg::Button::Create();
////    auto itemThreeButtonAlignment = sfg::Alignment::Create();
////    createImageButton(itemThreeButton, "  3  ",itemThreeButtonAlignment);
////
////    auto itemFourButton = sfg::Button::Create();
////    auto itemFourButtonAlignment = sfg::Alignment::Create();
////    createImageButton(itemFourButton, "  4  ",itemFourButtonAlignment);
////
////    auto itemFiveButton = sfg::Button::Create();
////    auto itemFiveButtonAlignment = sfg::Alignment::Create();
////    createImageButton(itemFiveButton, "  5  ", itemFiveButtonAlignment);
////
////    auto itemSixButton = sfg::Button::Create();
////    auto itemSixButtonAlignment = sfg::Alignment::Create();
////    createImageButton(itemSixButton, "  6  ", itemSixButtonAlignment);
////
////    /* ability buttons */
////    auto abilityOneButton = sfg::Button::Create();
////    auto abilityOneButtonAlignment = sfg::Alignment::Create();
////    createImageButton(abilityOneButton, "  7  ", abilityOneButtonAlignment);
////
////    auto abilityTwoButton = sfg::Button::Create();
////    auto abilityTwoButtonAlignment = sfg::Alignment::Create();
////    createImageButton(abilityOneButton, "  8  ", abilityTwoButtonAlignment);
////
////    auto abilityThreeButton = sfg::Button::Create();
////    auto abilityThreeButtonAlignment = sfg::Alignment::Create();
////    createImageButton(abilityThreeButton, "  9  ", abilityThreeButtonAlignment);
////
////    auto abilityFourButton = sfg::Button::Create();
////    auto abilityFourButtonAlignment = sfg::Alignment::Create();
////    createImageButton(abilityFourButton, "  0  ", abilityFourButtonAlignment);
//
//    /* Move buttons */
////    auto moveUpButton = sfg::Button::Create();
////    auto moveUpButtonAlignment = sfg::Alignment::Create();
////    createImageButton(moveUpButton, "  UP  ", moveUpButtonAlignment);
////
////    auto moveDownButton = sfg::Button::Create();
////    auto moveDownButtonAlignment = sfg::Alignment::Create();
////    createImageButton(moveDownButton, "  DOWN  ", moveDownButtonAlignment);
////
////    auto moveLeftButton = sfg::Button::Create();
////    auto moveLeftButtonAlignment = sfg::Alignment::Create();
////    createImageButton(moveLeftButton, "  LEFT  ", moveLeftButtonAlignment);
////
////    auto moveRightButton = sfg::Button::Create();
////    auto moveRightButtonAlignment = sfg::Alignment::Create();
////    createImageButton(moveRightButton, "  RIGHT  ", moveRightButtonAlignment);
//
//    // It is a 4-tuple (ignore the fact that it is a rect) containing
//    // in order: column index, row index, column span, row span.
//
//    semiTable->Attach(muteMusicButton, sf::Rect<sf::Uint32>(2,0,1,1), sfg::Table::EXPAND, sfg::Table::EXPAND, sf::Vector2f(0.f, 0.f));
//    semiTable->Attach(muteSoundButton, sf::Rect<sf::Uint32>(0,0,1,1), sfg::Table::EXPAND, sfg::Table::EXPAND, sf::Vector2f(0.f, 0.f));
//
////    buttonTable->Attach(itemOneButton, sf::Rect<sf::Uint32>(0,1,1,1), sfg::Table::EXPAND, sfg::Table::EXPAND, sf::Vector2f(0.f, 0.f));
////    buttonTable->Attach(itemTwoButton, sf::Rect<sf::Uint32>(1,1,1,1), sfg::Table::EXPAND, sfg::Table::EXPAND, sf::Vector2f(0.f, 0.f));
////    buttonTable->Attach(itemThreeButton, sf::Rect<sf::Uint32>(2,1,1,1), sfg::Table::EXPAND, sfg::Table::EXPAND, sf::Vector2f(0.f, 0.f));
////    buttonTable->Attach(itemFourButton, sf::Rect<sf::Uint32>(3,1,1,1), sfg::Table::EXPAND, sfg::Table::EXPAND, sf::Vector2f(0.f, 0.f));
////    buttonTable->Attach(itemFiveButton, sf::Rect<sf::Uint32>(4,1,1,1), sfg::Table::EXPAND, sfg::Table::EXPAND, sf::Vector2f(0.f, 0.f));
////    buttonTable->Attach(itemSixButton, sf::Rect<sf::Uint32>(5,1,1,1), sfg::Table::EXPAND, sfg::Table::EXPAND, sf::Vector2f(0.f, 0.f));
////
////    buttonTable->Attach(abilityOneButton, sf::Rect<sf::Uint32>(0,4,1,1), sfg::Table::EXPAND, sfg::Table::EXPAND, sf::Vector2f(0.f, 0.f));
////    buttonTable->Attach(abilityTwoButton, sf::Rect<sf::Uint32>(1,4,1,1), sfg::Table::EXPAND, sfg::Table::EXPAND, sf::Vector2f(0.f, 0.f));
////    buttonTable->Attach(abilityThreeButton, sf::Rect<sf::Uint32>(2,4,1,1), sfg::Table::EXPAND, sfg::Table::EXPAND, sf::Vector2f(0.f, 0.f));
////    buttonTable->Attach(abilityFourButton, sf::Rect<sf::Uint32>(3,4,1,1), sfg::Table::EXPAND, sfg::Table::EXPAND, sf::Vector2f(0.f, 0.f));
////
////    buttonTable->Attach(moveUpButton, sf::Rect<sf::Uint32>(0,6,1,1), sfg::Table::EXPAND, sfg::Table::EXPAND, sf::Vector2f(0.f, 0.f));
////    buttonTable->Attach(moveDownButton, sf::Rect<sf::Uint32>(1,6,1,1), sfg::Table::EXPAND, sfg::Table::EXPAND, sf::Vector2f(0.f, 0.f));
////    buttonTable->Attach(moveLeftButton, sf::Rect<sf::Uint32>(2,6,1,1), sfg::Table::EXPAND, sfg::Table::EXPAND, sf::Vector2f(0.f, 0.f));
////    buttonTable->Attach(moveRightButton, sf::Rect<sf::Uint32>(3,6,1,1), sfg::Table::EXPAND, sfg::Table::EXPAND, sf::Vector2f(0.f, 0.f));
//
//    auto alignmentBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
//    alignmentBox->Pack(semiTable);
//
//    auto alignmentButtonBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
//    alignmentButtonBox->Pack(buttonTable);
//
////    mainTable->Attach(defaultButton, sf::Rect<sf::Uint32>(0,0,1,1), sfg::Table::EXPAND, sfg::Table::EXPAND, sf::Vector2f(0.f, 0.f));
////    mainTable->Attach(applyButton, sf::Rect<sf::Uint32>(1,0,1,1), sfg::Table::EXPAND, sfg::Table::EXPAND, sf::Vector2f(0.f, 0.f));
//
//    desktop->SetProperty("Frame#frame", "FontSize", 50.f);
//
////    auto semiFrame = sfg::Frame::Create("Keybindings");
////    semiFrame->SetId("frame");
////    semiFrame->SetAlignment(sf::Vector2f(.5f, .5f));
////    semiFrame->Add(alignmentButtonBox);
//
//
//    auto mainFrame = sfg::Frame::Create("Settings");
//    mainFrame->SetId("frame");
//    mainFrame->SetAlignment(sf::Vector2f(.5f, .5f));
//    mainFrame->Add(alignmentBox);
////    mainFrame->Add(semiFrame);
//
//    box->Pack(mainFrame);
////    box->Pack(semiFrame);
    box->Pack(settingsLabel);
    settingsWindow->Add(box);
    desktop->Add(settingsWindow);
}

void StateSettings::draw() {
    sf::Text title("Left[2D]ie", game->getFont(), 140);
    title.setFillColor(sf::Color::Red);
    title.setPosition(275, 50);

    game->getWindow().draw(title);
}


void StateSettings::itemPositionOneClicked() {

}

void StateSettings::itemPositionTwoClicked() {

}

void StateSettings::itemPositionThreeClicked() {

}

void StateSettings::itemPositionFourClicked() {

}

void StateSettings::itemPositionFiveClicked() {

}

void StateSettings::itemPositionSixClicked() {

}

void StateSettings::abilityOneClicked() {

}

void StateSettings::abilityTwoClicked() {

}

void StateSettings::abilityThreeClicked() {

}

void StateSettings::abilityFourClicked() {

}

void StateSettings::moveUpClicked() {

}

void StateSettings::moveDownClicked() {

}

void StateSettings::moveLeftClicked() {

}

void StateSettings::moveRightClicked() {

}

void StateSettings::buttonMuteSoundClicked() {
    // Mute sound
}

void StateSettings::buttonMuteMusicClicked() {
    // Mute music
}

void StateSettings::buttonDefaultClicked() {
    // Get default values
}

void StateSettings::buttonApplyClicked() {
    // Save changes
}

void StateSettings::buttonBackClicked() {
    // Return to main menu
    game->getStateMachine().setState(StateMachine::StateID::MAIN_MENU);
}