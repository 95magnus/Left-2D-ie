#ifndef LEFT2DIE_STATESETTINGS_H
#define LEFT2DIE_STATESETTINGS_H

#include "StateBase.h"
#include "../Game.h"
#include <SFML/Graphics/Text.hpp>

class StateSettings : public StateBase {
public:
    StateSettings(Game* game);
    virtual ~StateSettings();

    void update();
    void draw();

    void pause();
    void resume();
    void initGui();

    void itemPositionOneClicked();
    void itemPositionTwoClicked();
    void itemPositionThreeClicked();
    void itemPositionFourClicked();
    void itemPositionFiveClicked();
    void itemPositionSixClicked();

    void abilityOneClicked();
    void abilityTwoClicked();
    void abilityThreeClicked();
    void abilityFourClicked();

    void moveUpClicked();
    void moveDownClicked();
    void moveLeftClicked();
    void moveRightClicked();

    void buttonMuteSoundClicked();
    void buttonMuteMusicClicked();

    void buttonDefaultClicked();
    void buttonApplyClicked();

    void buttonBackClicked();

protected:

    StateBase* statebase;
    sf::Font *font;
};

#endif //LEFT2DIE_STATESETTINGS_H
