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


//// Main Menu GUI
void StateBase::createButton(sfg::Button::Ptr buttonName, const sf::Vector2f &position) {
    desktop->SetProperty("Button#button", "FontSize", 70.f);

    buttonName->SetId("button");
    buttonName->SetPosition(position);
    buttonName->SetRequisition(sf::Vector2f(0.f, 85.f));

    desktop->Add(buttonName);
}

//// Single Player GUI
void StateBase::createSinglePlayerWindow(sfg::Window::Ptr windowName){
    windowName->SetId("singleplayerwindow");
    windowName->SetPosition(sf::Vector2f(0.f,0.f));
    windowName->SetRequisition(sf::Vector2f(game->getWindowSize()));
//    desktop->Add(windowName);
}

void StateBase::createPlayerBarLabel(sfg::Label::Ptr labelName) {
    desktop->SetProperty("Label#label", "FontSize", 53.f);
    labelName->SetId("label");
    desktop->Add(labelName);
}

void StateBase::createImageButton(sfg::ToggleButton::Ptr buttonName, const String &filename) {
    desktop->SetProperty("ToggleButton#ToggleButton", "FontName", "resources/fonts/feast-of-flesh-bb.italic.ttf");
    auto guiImage = new sf::Image();
    ResourceLoader loader("resources/");
    loader.loadGuiImage(guiImage, filename);

    auto sfgImage = sfg::Image::Create(*guiImage);
    buttonName->SetImage(sfgImage);
}

void StateBase::createImage(sfg::Image::Ptr image, const String &filename){
    auto temp = new sf::Image;
    if(temp->loadFromFile(filename)){
        image->SetImage(*temp);
    }
    image->SetRequisition(sf::Vector2f(game->getWindowSize()));
    desktop->Add(image);
}


//// Shop GUI
void StateBase::createShopGUIWindow(sfg::Window::Ptr windowName){
    windowName->SetRequisition(sf::Vector2f(game->getWindowSize()));
    windowName->SetId("shopwindow");
    windowName->SetPosition(sf::Vector2f(0.f,0.f));

    desktop->Add(windowName);
}

void StateBase::createShopButtonImage(sfg::Button::Ptr buttonName, const String &filename) {
    desktop->SetProperty("Nextbutton#nextbutton", "BackgroundColor", "#80808080");

    buttonName->SetId("nextbutton");

    auto guiImage = new sf::Image();
    ResourceLoader loader("resources/");
    loader.loadGuiImage(guiImage, filename);

    auto sfgImage = sfg::Image::Create(*guiImage);
    buttonName->SetImage(sfgImage);
}

void StateBase::createShopLabel(sf::Text* text, const sf::Vector2f &position){
    text->setPosition(position);
    text->setColor(sf::Color::White);
    text->setScale(sf::Vector2f(1.f,1.f));
}

//// Settings GUI
// Create settings windows
void StateBase::createSettingsWindow(sfg::Window::Ptr windowName, const sf::Vector2f &position) {
    desktop->SetProperty("Window#window", "BackgroundColor", "#303030FD");
    windowName->SetId("window");

    windowName->SetPosition(position);
    //Set window size
    windowName->SetRequisition(sf::Vector2f(580.f, 600.f));
    desktop->Add(windowName);
}

void StateBase::createSettingsFrame(sfg::Frame::Ptr frameName){
    frameName->SetAlignment(sf::Vector2f(.5f, .5f));
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
void StateBase::createSettingsControlGUIButtons(sfg::ToggleButton::Ptr buttonName) {
    desktop->SetProperty("SettingsButtonGui#settingscontrols", "FontSize", 0.f);
    buttonName->SetId("size30px");
}


