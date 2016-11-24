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
    // Main settings window
    auto settingsWindow = sfg::Window::Create(sfg::Window::Style::BACKGROUND);
    createSettingsWindow(settingsWindow, sf::Vector2f(222.0f, 200.0f));

    auto soundButton = sfg::Button::Create("Music & Sounds");
    createSettingsButton(soundButton);
    soundButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::initSoundSettingsClicked,this));

    auto controlsButton = sfg::Button::Create("Controls");
    createSettingsButton(controlsButton);
    controlsButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::initControlsSettings,this));

    auto doneButton = sfg::Button::Create("Back To Main Menu");
    createSettingsButton(doneButton);
    doneButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::getToMainMenu,this));

    auto maintable = sfg::Table::Create();
    maintable->Attach(soundButton, sf::Rect<sf::Uint32>(0,1,3,1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
    maintable->Attach(controlsButton, sf::Rect<sf::Uint32>(0,2,3,1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
    maintable->Attach(doneButton, sf::Rect<sf::Uint32>(0,3,3,1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));

    auto box = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL );

    auto tableAlignment = sfg::Alignment::Create();

    auto alignmentBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
    alignmentBox->Pack(tableAlignment, true, true);

    tableAlignment->Add(maintable);
    tableAlignment->SetScale(sf::Vector2f(.0f, .0f));
    tableAlignment->SetAlignment(sf::Vector2f(.5f, .5f));

    auto settingsFrame = sfg::Frame::Create("Settings");
    settingsFrame->SetId("settingsframe");
    settingsFrame->SetAlignment(sf::Vector2f(.5f, .5f));
    settingsFrame->Add(alignmentBox);

    box->Pack(settingsFrame);
    settingsWindow->Add(box);
    desktop->Add(settingsWindow);
}

void StateSettings::draw() {
    sf::Text title("Left[2D]ie", game->getFont(), 140);
    title.setFillColor(sf::Color::Red);
    title.setPosition(275, 50);

    game->getWindow().draw(title);
}

void StateSettings::initSoundSettingsClicked() {
    // Music and sounds settings window
    auto soundSettingsWindow = sfg::Window::Create(sfg::Window::Style::BACKGROUND);
    createSettingsWindow(soundSettingsWindow, sf::Vector2f(222.0f, 200.0f));

    auto backButton = sfg::Button::Create("Back");
    createSettingsButton(backButton);
    backButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onDestroyClick,this));

    auto muteSoundButton = sfg::CheckButton::Create("Mute Sound");
    createSoundGUIButton(muteSoundButton);
    muteSoundButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onMuteSoundButtonClicked,this));

    auto muteMusicButton = sfg::CheckButton::Create("Mute Music");
    createSoundGUIButton(muteMusicButton);
    muteMusicButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onMuteMusicButtonClicked,this));

    auto maintable = sfg::Table::Create();

    auto box = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL );
    maintable->Attach(muteSoundButton, sf::Rect<sf::Uint32>(0,0,3,2), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
    maintable->Attach(muteMusicButton, sf::Rect<sf::Uint32>(0,2,3,2), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
    maintable->Attach(backButton, sf::Rect<sf::Uint32>(0,6,3,2), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));

    auto tableAlignment = sfg::Alignment::Create();

    auto alignmentBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
    alignmentBox->Pack(tableAlignment, true, true);

    tableAlignment->Add(maintable);
    tableAlignment->SetScale(sf::Vector2f(.0f, .0f));
    tableAlignment->SetAlignment(sf::Vector2f(.5f, .5f));

    auto soundSettingFrame = sfg::Frame::Create("Music & Sounds");
    soundSettingFrame->SetId("childsettingsframe");
    soundSettingFrame->SetAlignment(sf::Vector2f(.5f, .5f));
    soundSettingFrame->Add(alignmentBox);

    box->Pack(soundSettingFrame);
    soundSettingsWindow->Add(box);
    desktop->Add(soundSettingsWindow);
}

void StateSettings::initControlsSettings() {
    auto controlsSettings = sfg::Window::Create(sfg::Window::Style::BACKGROUND);
    createSettingsWindow(controlsSettings, sf::Vector2f(222.0f, 200.0f));

    auto notebook = sfg::Notebook::Create();
    notebook->SetId("notebook");

    auto labelGameplay = sfg::Label::Create("Gameplay  ");
    createLabel(labelGameplay);

    auto labelInventory = sfg::Label::Create("Inventory  ");
    createLabel(labelInventory);

    auto labelAbilities = sfg::Label::Create("Abilities ");
    createLabel(labelAbilities);


    auto maintable = sfg::Table::Create();

    auto backButton = sfg::Button::Create("Back");
    createSettingsControlButtons(backButton);
    backButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onDestroyClick,this));

    auto applyButton = sfg::Button::Create("Apply");
    createSettingsControlButtons(applyButton);
    applyButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onApplyButtonClick,this));

    auto defaultButton = sfg::Button::Create("Default");
    createSettingsControlButtons(defaultButton);
    defaultButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onDefaultButtonClick,this));

    maintable->Attach(backButton, sf::Rect<sf::Uint32>(0,0,1,1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
    maintable->Attach(applyButton, sf::Rect<sf::Uint32>(1,0,1,1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
    maintable->Attach(defaultButton, sf::Rect<sf::Uint32>(2,0,1,1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));

    // Inner table
    auto itemTable = sfg::Table::Create();

    auto itemOneButton = sfg::Button::Create("1");
    createSettingsControlGUIButtons(itemOneButton);
    itemOneButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onItemOneButtonClick,this));

    auto itemTwoButton = sfg::Button::Create("2");
    createSettingsControlGUIButtons(itemTwoButton);
    itemTwoButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onItemTwoButtonClick,this));

    auto itemThreeButton = sfg::Button::Create("3");
    createSettingsControlGUIButtons(itemThreeButton);
    itemThreeButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onItemThreeButtonClick,this));

    auto itemFourButton = sfg::Button::Create("4");
    createSettingsControlGUIButtons(itemFourButton);
    itemFourButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onItemFourButtonClick,this));

    auto itemFiveButton = sfg::Button::Create("5");
    createSettingsControlGUIButtons(itemFiveButton);
    itemFiveButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onItemFiveButtonClick,this));

    auto itemSixButton = sfg::Button::Create("6");
    createSettingsControlGUIButtons(itemSixButton);
    itemSixButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onItemSixButtonClick,this));

    itemTable->Attach(itemOneButton, sf::Rect<sf::Uint32>(0,0,5,1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
    itemTable->Attach(itemTwoButton, sf::Rect<sf::Uint32>(0,1,5,1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
    itemTable->Attach(itemThreeButton, sf::Rect<sf::Uint32>(0,2,5,1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
    itemTable->Attach(itemFourButton, sf::Rect<sf::Uint32>(0,3,5,1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
    itemTable->Attach(itemFiveButton, sf::Rect<sf::Uint32>(0,4,5,1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));
    itemTable->Attach(itemSixButton, sf::Rect<sf::Uint32>(0,5,5,1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(10.f, 10.f));

    // Main box
    auto box = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL );

    auto tableOneAlignment = sfg::Alignment::Create();

    auto alignmentOneBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
    alignmentOneBox->Pack(tableOneAlignment, true, true);

    tableOneAlignment->Add(maintable);
    tableOneAlignment->SetScale(sf::Vector2f(.0f, .0f));
    tableOneAlignment->SetAlignment(sf::Vector2f(.5f, .5f));

    auto tableTwoAlignment = sfg::Alignment::Create();

    auto alignmentTwoBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
    alignmentTwoBox->Pack(tableTwoAlignment, true, true);

    tableTwoAlignment->Add(itemTable);
    tableTwoAlignment->SetScale(sf::Vector2f(.0f, .0f));
    tableTwoAlignment->SetAlignment(sf::Vector2f(.5f, .5f));

    auto soundSettingFrame = sfg::Frame::Create("Controls");
    soundSettingFrame->SetId("childsettingsframe");
    soundSettingFrame->SetAlignment(sf::Vector2f(.5f, .5f));
    soundSettingFrame->Add(alignmentOneBox);

    alignmentOneBox->Pack(alignmentTwoBox);
//    box->Pack(soundSettingFrame);
    box->Pack(alignmentOneBox);
  //  controlsSettings->Add(box);

    notebook->AppendPage(box, labelGameplay);
    notebook->AppendPage(sfg::Label::Create(), labelInventory);
    notebook->AppendPage(sfg::Label::Create(), labelAbilities);

    controlsSettings->Add(notebook);
    desktop->Add(controlsSettings);
}

void StateSettings::onDestroyClick() {
    // Obtain parent window
    auto widget = sfg::Context::Get().GetActiveWidget();

    while( widget->GetName() != "Window" ) {
        widget = widget->GetParent();
    }

    // Remove window from desktop
    desktop->Remove(widget);
}

void StateSettings::getToMainMenu() {
    // Return to main menu
    game->getStateMachine().setState(StateMachine::StateID::MAIN_MENU);
}


void StateSettings::onMuteSoundButtonClicked() {
    // Mute sound
}

void StateSettings::onMuteMusicButtonClicked() {
    // Mute music
}

void StateSettings::onDefaultButtonClick() {
    // Default values
}

void StateSettings::onApplyButtonClick() {
    // Apply changes
}

void StateSettings::onItemOneButtonClick() {

}

void StateSettings::onItemTwoButtonClick() {

}

void StateSettings::onItemThreeButtonClick() {

}

void StateSettings::onItemFourButtonClick() {

}

void StateSettings::onItemFiveButtonClick() {

}

void StateSettings::onItemSixButtonClick() {

}

void StateSettings::onAbilityOneButtonClick() {

}

void StateSettings::onAbilityTwoButtonClick() {

}

void StateSettings::onAbilityThreeButtonClick() {

}

void StateSettings::onAbilityFourButtonClick() {

}

void StateSettings::onMoveUpButtonClick() {

}

void StateSettings::onMoveDownButtonClick() {

}

void StateSettings::onMoveLeftButtonClick() {

}

void StateSettings::onMoveRightButtonClick() {

}