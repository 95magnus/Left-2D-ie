#include <SFML/System/InputStream.hpp>
#include "StateBase.h"
#include "../Game.h"

StateBase::StateBase(Game* game) {
    this->game = game;
    this->desktop = new sfg::Desktop();

    paused = false;

    desktop->LoadThemeFromFile(themePath);
}

StateBase::~StateBase() {
    delete desktop;
}

void StateBase::updateDesktop() {
    desktop->Update(timer.getElapsedTime().asMilliseconds());
    timer.restart();
}

//// Single Player GUI
void StateBase::createPlayerBarLabel(sfg::Label::Ptr labelName) {
    desktop->SetProperty("Label#label", "FontSize", 53.f);
    labelName->SetId("label");
}

void StateBase::createImageButton(sfg::ToggleButton::Ptr buttonName, const String &filename) {
    desktop->SetProperties("GuiButton#guibutton {"
                                   "	BorderColor: #FFFFFFFF;"
                                   "}"
                                   "GuiButton#guibutton:PRELIGHT {"
                                   "	BorderColor: #FFFFFFFF;"
                                   "    BorderWidth: 5;"
                                   "}"
                                   "GuiButton#guibutton:ACTIVE{"
                                   "	BorderColor: #FFFFFFFF"
                                   "	BorderWidth: 10;"
                                   "}"
    );

    auto guiImage = new sf::Image();
    ResourceLoader loader("resources/");
    loader.loadGuiImage(guiImage, filename);

//    buttonName->SetId("guibutton");

    auto sfgImage = sfg::Image::Create(*guiImage);
    buttonName->SetImage(sfgImage);
}

//// Shop GUI
void StateBase::createShopGUIWindow(sfg::Window::Ptr windowName){
    desktop->SetProperty("ShopWindow#shopwindow", "BackgroundColor", "#696969FF");

    windowName->SetId("shopwindow");
    //Set window size
    windowName->SetRequisition(sf::Vector2f(1024.f, 720.f));
    desktop->Add(windowName);
}

void StateBase::createShopButtonImage(sfg::Button::Ptr buttonName, const String &filename) {
    desktop->SetProperties("GuiButton#guibutton {"
                                   "	BorderColor: #FFFFFFFF;"
                                   "}"
                                   "GuiButton#guibutton:PRELIGHT {"
                                   "	BorderColor: #FFFFFFFF;"
                                   "    BorderWidth: 5;"
                                   "}"
                                   "GuiButton#guibutton:ACTIVE{"
                                   "	BorderColor: #FFFFFFFF"
                                   "	BorderWidth: 10;"
                                   "}"
    );

    auto guiImage = new sf::Image();
    ResourceLoader loader("resources/");
    loader.loadGuiImage(guiImage, filename);

//    buttonName->SetId("guibutton");

    auto sfgImage = sfg::Image::Create(*guiImage);
    buttonName->SetImage(sfgImage);
}

//// Settings GUI
// Main menu buttons
void StateBase::createButton(sfg::Button::Ptr buttonName, const sf::Vector2f &position) {
    desktop->SetProperty("Button#button", "FontSize", 70.f);

    buttonName->SetId("button");
    buttonName->SetPosition(position);
    buttonName->SetRequisition(sf::Vector2f(0.f, 85.f));

    desktop->Add(buttonName);
}

// Create settings windows
void StateBase::createSettingsWindow(sfg::Window::Ptr windowName, const sf::Vector2f &position) {
    desktop->SetProperty("SettingsWindow#settingswindow", "BackgroundColor", "#696969FF");
    windowName->SetId("settingswindow");

    windowName->SetPosition(position);
    //Set window size
    windowName->SetRequisition(sf::Vector2f(580.f, 600.f));
    desktop->Add(windowName);
}

// Settings button
void StateBase::createSettingsButton(sfg::Button::Ptr buttonName) {
    desktop->SetProperty("SettingsButton#settingsbutton", "FontSize", 0.f);
    buttonName->SetAllocation(sf::FloatRect(100.f, 100.0f, 100.f, 100.f));
    buttonName->SetId("size50px");
}

// Sound settings checkbuttons
void StateBase::createSoundGUIButton(sfg::CheckButton::Ptr checkButtonName) {
    desktop->SetProperty("SettingsButtonGui#settingsbuttongui", "FontSize", 0.f);
    checkButtonName->SetId("size50px");
}

// Back, default and apply buttons
void StateBase::createSettingsControlButtons(sfg::Button::Ptr buttonName) {
    desktop->SetProperty("SettingsButton#settingscontrols", "FontSize", 0.f);
    buttonName->SetAllocation(sf::FloatRect(100.f, 100.0f, 100.f, 100.f));
    buttonName->SetId("size30px");
}

// Notebook labels
void StateBase::createLabel(sfg::Label::Ptr labelName) {
    desktop->SetProperty("Label#label", "FontSize", 35.f);
    labelName->SetId("label");
}

// All other settings label
void StateBase::createSettingsLabel(sfg::Label::Ptr labelName){
    desktop->SetProperty("SettingsLabel#settingslabel", "FontSize", 0.f);
    labelName->SetId("size30px");
}

// All other settings buttons
void StateBase::createSettingsControlGUIButtons(sfg::Button::Ptr buttonName) {
    desktop->SetProperty("SettingsButtonGui#settingscontrols", "FontSize", 0.f);
    buttonName->SetId("size30px");
}


