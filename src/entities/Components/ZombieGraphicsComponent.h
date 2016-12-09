//
// Created by MortenSuvatne on 31.10.2016.
//

#ifndef LEFT2DIE_ZOMBIEGRAPHICSCOMPONENT_H
#define LEFT2DIE_ZOMBIEGRAPHICSCOMPONENT_H

#include "GraphicsComponent.h"
#include "GameObject.h"
#include "ZombiePhysicsComponent.h"

class ZombieGraphicsComponent : GraphicsComponent {
public:
    ZombieGraphicsComponent(ZombieGraphicsComponent* physics) : physics_(physics){}

    virtual void update(GameObject& obj, Graphics& graphics){
        //TODO: Implement Zombie graphics here
    }

private:
};


#endif //LEFT2DIE_ZOMBIEGRAPHICSCOMPONENT_H
