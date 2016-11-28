#include <SFML/System/InputStream.hpp>
#include "StateBase.h"

StateBase::StateBase(Game* game) {
    this->game = game;
    paused = false;
    desktop = new sfg::Desktop();
    desktop->LoadThemeFromFile(themePath);
}

StateBase::~StateBase() {
    delete desktop;
}

void StateBase::updateDesktop() {
    desktop->Update(timer.getElapsedTime().asMilliseconds());
    timer.restart();
}

void StateBase::createButton(sfg::Button::Ptr buttonName, const sf::Vector2f &position) {
    desktop->SetProperty("Button#button", "FontSize", 70.f);

    buttonName->SetId("button");
    buttonName->SetPosition(position);
    buttonName->SetRequisition(sf::Vector2f(0.f, 85.f));

    desktop->Add(buttonName);
}

void StateBase::createSettingsWindow(sfg::Window::Ptr windowName, const sf::Vector2f &position) {
    desktop->SetProperty("Window#window", "FontSize", 150.f);

    windowName->SetId("window");
    windowName->SetPosition(position);

    //Set window size
    windowName->SetRequisition(sf::Vector2f(580.f, 600.f));
    desktop->Add(windowName);
}

void StateBase::createSettingsButton(sfg::Button::Ptr buttonName) {
    desktop->SetProperty("SettingsButton#settingsbutton", "FontSize", 0.f);
    buttonName->SetAllocation(sf::FloatRect(100.f, 100.0f, 100.f, 100.f));
    buttonName->SetId("settingsbutton");
}

void StateBase::createSoundGUIButton(sfg::CheckButton::Ptr checkButtonName) {
    desktop->SetProperty("SettingsButtonGui#settingsbuttongui", "FontSize", 70.f);
    checkButtonName->SetId("settingsbuttongui");
}

void StateBase::createSettingsControlButtons(sfg::Button::Ptr buttonName) {
    desktop->SetProperty("SettingsButton#settingscontrols", "FontSize", 50.f);
    buttonName->SetAllocation(sf::FloatRect(100.f, 100.0f, 100.f, 100.f));
    buttonName->SetId("settingscontrols");
}

void StateBase::createLabel(sfg::Label::Ptr labelName) {
    desktop->SetProperty("Label#label", "FontSize", 35.f);
    labelName->SetId("label");
}


void StateBase::createSettingsLabel(sfg::Label::Ptr labelName){
    desktop->SetProperty("SettingsLabel#settingslabel", "FontSize", 40.f);
    labelName->SetId("settingslabel");
}

void StateBase::createSettingsControlGUIButtons(sfg::Button::Ptr buttonName) {
    desktop->SetProperty("SettingsButtonGui#settingscontrols", "FontSize", 50.f);
    buttonName->SetId("settingscontrolsgui");
}



void StateBase::createImageButton(sfg::Button::Ptr imageButton, const String &label, sfg::Alignment::Ptr alignmentName) {
    desktop->SetProperty("ImageButton#imagebutton", "FontSize", 0.f);
    imageButton->SetLabel(label);

    imageButton->SetId("imagebutton");
    imageButton->SetRequisition(sf::Vector2f(0.f, 69.f));
    alignmentName->Add(imageButton);
}

//void StateBase::createImageButton(sfg::Button::Ptr buttonName, const String text, const String &filename) {
//    desktop->SetProperty("GuiButton#guibutton", "FontSize", 70.f);
//
//    auto guiImage = new sf::Image();
//    ResourceLoader loader("resources/");
//    loader.loadGuiImage(guiImage, filename);
//
//    buttonName->SetId("guibutton");
//    buttonName->SetRequisition(sf::Vector2f(0.f, 85.0f));
//
//    auto sfgImage = sfg::Image::Create(*guiImage);
//    buttonName->SetLabel(text);
//    buttonName->SetImage(sfgImage);
//}


