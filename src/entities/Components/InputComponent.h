//
// Created by MortenSuvatne on 30.10.2016.
//

#ifndef LEFT2DIE_INPUTCOMPONENT_H
#define LEFT2DIE_INPUTCOMPONENT_H

#include "../Player.h"
#include "GameObject.h"

class InputComponent {
public:
    virtual ~InputComponent() {}
    virtual void update(GameObject& gameObject) = 0;

};


#endif //LEFT2DIE_INPUTCOMPONENT_H
