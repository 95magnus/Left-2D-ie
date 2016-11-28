#ifndef LEFT2DIE_STATEBASE_H
#define LEFT2DIE_STATEBASE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFGUI/Widgets.hpp>
#include "../util/ResourceLoader.h"

class Game;
typedef std::string String;

class StateBase {
public:
    virtual ~StateBase();

    //virtual void init() = 0;

    virtual void update() = 0;
    virtual void draw() = 0;

    virtual void pause() { paused = true; }
    virtual void resume() { paused = false; }

    sfg::Desktop* getDesktop() const { return desktop; }
    void updateDesktop();

    // Main menu buttons
    virtual void createButton(sfg::Button::Ptr buttonName, const sf::Vector2f &position);

    // Create settings winddows
    virtual void createSettingsWindow(sfg::Window::Ptr windowName, const sf::Vector2f &position);

    // Settings button
    virtual void createSettingsButton(sfg::Button::Ptr buttonName);

    // Sound settings checkbuttons
    virtual void createSoundGUIButton(sfg::CheckButton::Ptr checkButtonName);

    // Back, default and apply buttons
    virtual void createSettingsControlButtons(sfg::Button::Ptr buttonName);

    // Notebook labels
    virtual void createLabel(sfg::Label::Ptr labelName);

    // All other settings label
    virtual void createSettingsLabel(sfg::Label::Ptr labelName);

    // All other settings buttons
    virtual void createSettingsControlGUIButtons(sfg::Button::Ptr buttonName);

    void createImageButton(sfg::Button::Ptr imageButton, const String &label, sfg::Alignment::Ptr alignmentName);

protected:
    StateBase(Game* game);

    Game* game;
    sfg::Desktop* desktop;
    sf::Clock timer;

    const String themePath = "resources/gui/theme.css";

    bool paused;

};

#endif //LEFT2DIE_STATEBASE_H
