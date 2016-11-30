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


void StateSettings::update(float deltaTime) {

}

void StateSettings::initGui() {
    // Main settings window
    auto settingsWindow = sfg::Window::Create(sfg::Window::Style::BACKGROUND);
    createSettingsWindow(settingsWindow, sf::Vector2f(222.0f, 85.0f));

    // Widgets
    auto soundButton = sfg::Button::Create("Music & Sounds");
    createSettingsButton(soundButton);

    auto controlsButton = sfg::Button::Create("Controls");
    createSettingsButton(controlsButton);

    auto doneButton = sfg::Button::Create("Back To Main Menu");
    createSettingsButton(doneButton);

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

    // Signals
    soundButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::initSoundSettingsClicked,this));
    controlsButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::initControlsSettings,this));
    doneButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::getToMainMenu,this));
}

void StateSettings::draw() {
    sf::Text title("Left[2D]ie", game->getFont(), 140);
    title.setColor(sf::Color::Red);
    title.setPosition(275, 50);
    game->getWindow().draw(title);
}

void StateSettings::initSoundSettingsClicked() {
    // Music and sounds settings window
    auto soundSettingsWindow = sfg::Window::Create(sfg::Window::Style::BACKGROUND);
    createSettingsWindow(soundSettingsWindow, sf::Vector2f(222.0f, 85.0f));

    // Widgets
    auto backButton = sfg::Button::Create("Back");
    createSettingsButton(backButton);

    auto muteSoundButton = sfg::CheckButton::Create("  Mute Sound");
    createSoundGUIButton(muteSoundButton);

    auto muteMusicButton = sfg::CheckButton::Create("  Mute Music");
    createSoundGUIButton(muteMusicButton);

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
    soundSettingFrame->SetId("soundsettingsframe");
    soundSettingFrame->SetAlignment(sf::Vector2f(.5f, .5f));
    soundSettingFrame->Add(alignmentBox);

    box->Pack(soundSettingFrame);
    soundSettingsWindow->Add(box);
    desktop->Add(soundSettingsWindow);

    // Signals
    backButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onDestroyClick,this));
    muteSoundButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onMuteSoundButtonClicked,this));
    muteMusicButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onMuteMusicButtonClicked,this));
}

void StateSettings::initControlsSettings() {
    // Gameplay window
    auto mainWindow = sfg::Window::Create(sfg::Window::Style::BACKGROUND);
    createSettingsWindow(mainWindow, sf::Vector2f(222.0f, 85.0f));
    desktop->SetProperty("*", "FontName", "resources/fonts/feast-of-flesh-bb.italic.ttf");


    // Notebook labels
    auto labelGameplay = sfg::Label::Create("  Gameplay ");
    createLabel(labelGameplay);

    auto labelInventory = sfg::Label::Create(" Inventory  ");
    createLabel(labelInventory);

    auto labelAbilities = sfg::Label::Create(" Abilities  ");
    createLabel(labelAbilities);


    // Inventory labels
    auto actionLabel = sfg::Label::Create("Actions");
    createLabel(actionLabel);

    auto keysLabel = sfg::Label::Create("Keys");
    createLabel(keysLabel);

    auto itemOneLabel = sfg::Label::Create("    Item 1");
    createSettingsLabel(itemOneLabel);

    auto itemTwoLabel = sfg::Label::Create("    Item 2");
    createSettingsLabel(itemTwoLabel);

    auto itemThreeLabel = sfg::Label::Create("    Item 3");
    createSettingsLabel(itemThreeLabel);

    auto itemFourLabel = sfg::Label::Create("    Item 4");
    createSettingsLabel(itemFourLabel);

    auto itemFiveLabel = sfg::Label::Create("    Item 5");
    createSettingsLabel(itemFiveLabel);

    auto itemSixLabel = sfg::Label::Create("    Item 6");
    createSettingsLabel(itemSixLabel);

    // Gameplay labels
    auto actionLabel1 = sfg::Label::Create("     Actions");
    createLabel(actionLabel1);

    auto keysLabel1 = sfg::Label::Create("     Keys");
    createLabel(keysLabel1);

    auto attackLabel = sfg::Label::Create("Attack");
    createSettingsLabel(attackLabel);

    auto moveUpLabel = sfg::Label::Create("  Move up");
    createSettingsLabel(moveUpLabel);

    auto moveDownLabel = sfg::Label::Create("       Move down");
    createSettingsLabel(moveDownLabel);

    auto moveLeftLabel = sfg::Label::Create("    Move left");
    createSettingsLabel(moveLeftLabel);

    auto moveRightLabel = sfg::Label::Create("     Move right");
    createSettingsLabel(moveRightLabel);

    // Ability labels
    auto actionLabel2 = sfg::Label::Create("    Actions");
    createLabel(actionLabel2);

    auto keysLabel2 = sfg::Label::Create("    Keys");
    createLabel(keysLabel2);

    auto abilityOneLabel = sfg::Label::Create("       Ability 1");
    createSettingsLabel(abilityOneLabel);

    auto abilityTwoLabel = sfg::Label::Create("       Ability 2");
    createSettingsLabel(abilityTwoLabel);

    auto abilityThreeLabel = sfg::Label::Create("       Ability 3");
    createSettingsLabel(abilityThreeLabel);

    auto abilityFourLabel = sfg::Label::Create("       Ability 4");
    createSettingsLabel(abilityFourLabel);


    // Inventory buttons
    auto itemOneButton = sfg::Button::Create("          1");
    createSettingsControlGUIButtons(itemOneButton);

    auto itemTwoButton = sfg::Button::Create("          2");
    createSettingsControlGUIButtons(itemTwoButton);

    auto itemThreeButton = sfg::Button::Create("          3");
    createSettingsControlGUIButtons(itemThreeButton);

    auto itemFourButton = sfg::Button::Create("          4");
    createSettingsControlGUIButtons(itemFourButton);

    auto itemFiveButton = sfg::Button::Create("          5");
    createSettingsControlGUIButtons(itemFiveButton);

    auto itemSixButton = sfg::Button::Create("          6");
    createSettingsControlGUIButtons(itemSixButton);

    // Ability buttons
    auto abilityOneButton = sfg::Button::Create("       7");
    createSettingsControlGUIButtons(abilityOneButton);

    auto abilityTwoButton = sfg::Button::Create("       8");
    createSettingsControlGUIButtons(abilityTwoButton);

    auto abilityThreeButton = sfg::Button::Create("       9");
    createSettingsControlGUIButtons(abilityThreeButton);

    auto abilityFourButton = sfg::Button::Create("       0");
    createSettingsControlGUIButtons(abilityFourButton);

    // Gameplay buttons
    auto attackButton = sfg::Button::Create("     MOUSE LEFT");
    createSettingsControlGUIButtons(attackButton);

    auto moveUpButton = sfg::Button::Create(" MOVE UP");
    createSettingsControlGUIButtons(moveUpButton);

    auto moveDownButton = sfg::Button::Create("      MOVE DOWN");
    createSettingsControlGUIButtons(moveDownButton);

    auto moveLeftButton = sfg::Button::Create("   MOVE LEFT");
    createSettingsControlGUIButtons(moveLeftButton);

    auto moveRightButton = sfg::Button::Create("     MOVE RIGHT");
    createSettingsControlGUIButtons(moveRightButton);

    // Handle buttons
    auto backButton = sfg::Button::Create("  Back  ");
    createSettingsControlButtons(backButton);

    auto applyButton = sfg::Button::Create("   Apply   ");
    createSettingsControlButtons(applyButton);

    auto defaultButton = sfg::Button::Create(" Default  ");
    createSettingsControlButtons(defaultButton);

    auto backButton1 = sfg::Button::Create("  Back  ");
    createSettingsControlButtons(backButton1);

    auto applyButton1 = sfg::Button::Create("   Apply   ");
    createSettingsControlButtons(applyButton1);

    auto defaultButton1 = sfg::Button::Create(" Default  ");
    createSettingsControlButtons(defaultButton1);

    auto backButton2 = sfg::Button::Create("  Back  ");
    createSettingsControlButtons(backButton2);

    auto applyButton2 = sfg::Button::Create("   Apply   ");
    createSettingsControlButtons(applyButton2);

    auto defaultButton2 = sfg::Button::Create(" Default  ");
    createSettingsControlButtons(defaultButton2);

    // Toolbar for handle buttons
    auto boxToolbar1 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
    boxToolbar1->SetSpacing(5.f);
    boxToolbar1->Pack(backButton, false);
    boxToolbar1->Pack(applyButton, false);
    boxToolbar1->Pack(defaultButton, false);

    auto boxToolbar2 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
    boxToolbar2->SetSpacing(5.f);
    boxToolbar2->Pack(backButton1, false);
    boxToolbar2->Pack(applyButton1, false);
    boxToolbar2->Pack(defaultButton1, false);

    auto boxToolbar3 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
    boxToolbar3->SetSpacing(5.f);
    boxToolbar3->Pack(backButton2, false);
    boxToolbar3->Pack(applyButton2, false);
    boxToolbar3->Pack(defaultButton2, false);

    auto mainframe1 = sfg::Frame::Create();
    mainframe1->Add(boxToolbar1);
    mainframe1->SetId("frame");

    auto mainframe2 = sfg::Frame::Create();
    mainframe2->Add(boxToolbar2);
    mainframe2->SetId("frame");

    auto mainframe3 = sfg::Frame::Create();
    mainframe3->Add(boxToolbar3);
    mainframe3->SetId("frame");

    // Table to manage label and button position
    auto gameplayTable = sfg::Table::Create();
    gameplayTable->Attach(actionLabel, sf::Rect<sf::Uint32>(0,0,2,1), sfg::Table::FILL , sfg::Table::FILL | sfg::Table::EXPAND, sf::Vector2f(0.f, 0.f));
    gameplayTable->Attach(keysLabel, sf::Rect<sf::Uint32>(5,0,2,1), sfg::Table::FILL , sfg::Table::FILL | sfg::Table::EXPAND, sf::Vector2f(0.f, 0.f));
    gameplayTable->Attach(attackLabel, sf::Rect<sf::Uint32>(0,1,2,1), sfg::Table::FILL , sfg::Table::FILL | sfg::Table::EXPAND);
    gameplayTable->Attach(attackButton, sf::Rect<sf::Uint32>(5,1,1,1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));
    gameplayTable->Attach(moveUpLabel, sf::Rect<sf::Uint32>(0,2,2,1), sfg::Table::FILL , sfg::Table::FILL | sfg::Table::EXPAND);
    gameplayTable->Attach(moveUpButton, sf::Rect<sf::Uint32>(5,2,1,1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));
    gameplayTable->Attach(moveDownLabel, sf::Rect<sf::Uint32>(0,3,2,1), sfg::Table::FILL , sfg::Table::FILL | sfg::Table::EXPAND);
    gameplayTable->Attach(moveDownButton, sf::Rect<sf::Uint32>(5,3,1,1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));
    gameplayTable->Attach(moveLeftLabel, sf::Rect<sf::Uint32>(0,4,2,1), sfg::Table::FILL , sfg::Table::FILL | sfg::Table::EXPAND);
    gameplayTable->Attach(moveLeftButton, sf::Rect<sf::Uint32>(5,4,1,1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));
    gameplayTable->Attach(moveRightLabel, sf::Rect<sf::Uint32>(0,5,2,1), sfg::Table::FILL , sfg::Table::FILL | sfg::Table::EXPAND);
    gameplayTable->Attach(moveRightButton, sf::Rect<sf::Uint32>(5,5,1,1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));

    auto inventoryTable = sfg::Table::Create();
    inventoryTable->Attach(actionLabel1, sf::Rect<sf::Uint32>(0,0,2,1), sfg::Table::FILL , sfg::Table::FILL | sfg::Table::EXPAND, sf::Vector2f(0.f, 0.f));
    inventoryTable->Attach(keysLabel1, sf::Rect<sf::Uint32>(5,0,2,1), sfg::Table::FILL , sfg::Table::FILL | sfg::Table::EXPAND, sf::Vector2f(0.f, 0.f));
    inventoryTable->Attach(itemOneLabel, sf::Rect<sf::Uint32>(0,1,2,1), sfg::Table::FILL , sfg::Table::FILL | sfg::Table::EXPAND);
    inventoryTable->Attach(itemOneButton, sf::Rect<sf::Uint32>(5,1,1,1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));
    inventoryTable->Attach(itemTwoLabel, sf::Rect<sf::Uint32>(0,2,2,1), sfg::Table::FILL , sfg::Table::FILL | sfg::Table::EXPAND);
    inventoryTable->Attach(itemTwoButton, sf::Rect<sf::Uint32>(5,2,1,1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));
    inventoryTable->Attach(itemThreeLabel, sf::Rect<sf::Uint32>(0,3,2,1), sfg::Table::FILL , sfg::Table::FILL | sfg::Table::EXPAND);
    inventoryTable->Attach(itemThreeButton, sf::Rect<sf::Uint32>(5,3,1,1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));
    inventoryTable->Attach(itemFourLabel, sf::Rect<sf::Uint32>(0,4,2,1), sfg::Table::FILL , sfg::Table::FILL | sfg::Table::EXPAND);
    inventoryTable->Attach(itemFourButton, sf::Rect<sf::Uint32>(5,4,1,1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));
    inventoryTable->Attach(itemFiveLabel, sf::Rect<sf::Uint32>(0,5,2,1), sfg::Table::FILL , sfg::Table::FILL | sfg::Table::EXPAND);
    inventoryTable->Attach(itemFiveButton, sf::Rect<sf::Uint32>(5,5,1,1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));
    inventoryTable->Attach(itemSixLabel, sf::Rect<sf::Uint32>(0,6,2,1), sfg::Table::FILL , sfg::Table::FILL | sfg::Table::EXPAND);
    inventoryTable->Attach(itemSixButton, sf::Rect<sf::Uint32>(5,6,1,1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));

    auto abilityTable = sfg::Table::Create();
    abilityTable->Attach(actionLabel2, sf::Rect<sf::Uint32>(0,0,2,1), sfg::Table::FILL , sfg::Table::FILL | sfg::Table::EXPAND, sf::Vector2f(0.f, 0.f));
    abilityTable->Attach(keysLabel2, sf::Rect<sf::Uint32>(5,0,2,1), sfg::Table::FILL , sfg::Table::FILL | sfg::Table::EXPAND, sf::Vector2f(0.f, 0.f));
    abilityTable->Attach(abilityOneLabel, sf::Rect<sf::Uint32>(0,1,2,1), sfg::Table::FILL , sfg::Table::FILL | sfg::Table::EXPAND);
    abilityTable->Attach(abilityOneButton, sf::Rect<sf::Uint32>(5,1,1,1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));
    abilityTable->Attach(abilityTwoLabel, sf::Rect<sf::Uint32>(0,2,2,1), sfg::Table::FILL , sfg::Table::FILL | sfg::Table::EXPAND);
    abilityTable->Attach(abilityTwoButton, sf::Rect<sf::Uint32>(5,2,1,1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));
    abilityTable->Attach(abilityThreeLabel, sf::Rect<sf::Uint32>(0,3,2,1), sfg::Table::FILL , sfg::Table::FILL | sfg::Table::EXPAND);
    abilityTable->Attach(abilityThreeButton, sf::Rect<sf::Uint32>(5,3,1,1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));
    abilityTable->Attach(abilityFourLabel, sf::Rect<sf::Uint32>(0,4,2,1), sfg::Table::FILL , sfg::Table::FILL | sfg::Table::EXPAND);
    abilityTable->Attach(abilityFourButton, sf::Rect<sf::Uint32>(5,4,1,1), sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL, sf::Vector2f(0.f, 0.f));

    // Separator
    auto separator1 = sfg::Separator::Create( sfg::Separator::Orientation::HORIZONTAL );
    auto separator2 = sfg::Separator::Create( sfg::Separator::Orientation::HORIZONTAL );
    auto separator3 = sfg::Separator::Create( sfg::Separator::Orientation::HORIZONTAL );

    // Boxes
    auto gameplayBox = sfg::Box::Create( sfg::Box::Orientation::VERTICAL );
    gameplayBox->Pack(gameplayTable, true);
    gameplayBox->Pack(separator1, false);
    gameplayBox->Pack(mainframe1, false);

    auto inventoryBox = sfg::Box::Create( sfg::Box::Orientation::VERTICAL );
    inventoryBox->Pack(inventoryTable, true);
    inventoryBox->Pack(separator2, false);
    inventoryBox->Pack(mainframe2, false);

    auto abilityBox = sfg::Box::Create( sfg::Box::Orientation::VERTICAL );
    abilityBox->Pack(abilityTable, true);
    abilityBox->Pack(separator3, false);
    abilityBox->Pack(mainframe3, false);

    // Notebook
    auto notebook1 = sfg::Notebook::Create();
    notebook1->SetId("notebook");
    notebook1->AppendPage(gameplayBox, labelGameplay);
    notebook1->AppendPage(inventoryBox, labelInventory);
    notebook1->AppendPage(abilityBox, labelAbilities);

    mainWindow->Add(notebook1);
    desktop->Add(mainWindow);

    // Signals
    backButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onDestroyClick,this));
    applyButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onApplyButtonClick,this));
    defaultButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onDefaultButtonClick,this));

    backButton1->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onDestroyClick,this));
    applyButton1->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onApplyButtonClick,this));
    defaultButton1->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onDefaultButtonClick,this));

    backButton2->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onDestroyClick,this));
    applyButton2->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onApplyButtonClick,this));
    defaultButton2->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onDefaultButtonClick,this));

    attackButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onDestroyClick,this));
    moveUpButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onMoveUpButtonClick,this));
    moveDownButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onMoveDownButtonClick,this));
    moveLeftButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onMoveLeftButtonClick,this));
    moveRightButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onMoveRightButtonClick,this));

    itemOneButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onItemOneButtonClick,this));
    itemTwoButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onItemTwoButtonClick,this));
    itemThreeButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onItemThreeButtonClick,this));
    itemFourButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onItemFourButtonClick,this));
    itemFiveButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onItemFiveButtonClick,this));
    itemSixButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onItemSixButtonClick,this));

    abilityOneButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onAbilityOneButtonClick,this));
    abilityTwoButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onAbilityTwoButtonClick,this));
    abilityThreeButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onAbilityThreeButtonClick,this));
    abilityFourButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&StateSettings::onAbilityFourButtonClick,this));
}

void StateSettings::onDestroyClick() {
    // Obtain parent window
    auto widget = sfg::Context::Get().GetActiveWidget();

    while(widget->GetName() != "Window") {
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
    // Item 1
}

void StateSettings::onItemTwoButtonClick() {
    // Item 2
}

void StateSettings::onItemThreeButtonClick() {
    // Item 3
}

void StateSettings::onItemFourButtonClick() {
    // Item 4
}

void StateSettings::onItemFiveButtonClick() {
    // Item 5
}

void StateSettings::onItemSixButtonClick() {
    // Item 6
}

void StateSettings::onAbilityOneButtonClick() {
    // Ability 1
}

void StateSettings::onAbilityTwoButtonClick() {
    // Ability 2
}

void StateSettings::onAbilityThreeButtonClick() {
    // Ability 3
}

void StateSettings::onAbilityFourButtonClick() {
    // Ability 4
}

void StateSettings::onMoveUpButtonClick() {
    // Move up
}

void StateSettings::onMoveDownButtonClick() {
    // Move down
}

void StateSettings::onMoveLeftButtonClick() {
    // Move left
}

void StateSettings::onMoveRightButtonClick() {
    // Move right
}