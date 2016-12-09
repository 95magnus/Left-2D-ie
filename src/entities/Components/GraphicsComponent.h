//
// Created by MortenSuvatne on 30.10.2016.
//

#ifndef LEFT2DIE_GRAPHICSCOMPONENT_H
#define LEFT2DIE_GRAPHICSCOMPONENT_H

#include "GameObject.h"

class GraphicsComponent {
public:
    virtual ~GraphicsComponent() {}
    virtual void update(GameObject& obj, World& world) = 0;
};


#endif //LEFT2DIE_GRAPHICSCOMPONENT_H
