#ifndef LEFT2DIE_STATESETTINGS_H
#define LEFT2DIE_STATESETTINGS_H

#include "StateBase.h"
#include "../Game.h"
#include <SFML/Graphics/Text.hpp>

class StateSettings : public StateBase {
public:
    StateSettings(Game* game);
    virtual ~StateSettings();

    void update(float deltaTime);
    void draw(sf::RenderWindow &window);

    void pause();
    void resume();
    void initGui();
    void initSoundSettingsClicked();
    void initControlsSettings();

    void onItemOneButtonClick();
    void onItemTwoButtonClick();
    void onItemThreeButtonClick();
    void onItemFourButtonClick();
    void onItemFiveButtonClick();
    void onItemSixButtonClick();

    void onAbilityOneButtonClick();
    void onAbilityTwoButtonClick();
    void onAbilityThreeButtonClick();
    void onAbilityFourButtonClick();

    void onMoveUpButtonClick();
    void onMoveDownButtonClick();
    void onMoveLeftButtonClick();
    void onMoveRightButtonClick();

    void onMuteSoundButtonClicked();
    void onMuteMusicButtonClicked();

    void onDefaultButtonClick();
    void onApplyButtonClick();

    void getToMainMenu();
    void onDestroyClick();

protected:
    StateBase* statebase;
    sf::Font *font;
};

#endif //LEFT2DIE_STATESETTINGS_H
