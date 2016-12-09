//
// Created by MortenSuvatne on 31.10.2016.
//

#ifndef LEFT2DIE_PLAYERGRAPHICSCOMPONENT_H
#define LEFT2DIE_PLAYERGRAPHICSCOMPONENT_H

#include "GraphicsComponent.h"
#include "GameObject.h"
#include "PlayerPhysicsComponent.h"

class PlayerGraphicsComponent : GraphicsComponent{
public:
    PlayerGraphicsComponent(PlayerPhysicsComponent* physics) : physics_(physics){}


    virtual void update(GameObject& obj, Graphics& graphics){
        //TODO: Implement graphics code for player
    }

private:
};


#endif //LEFT2DIE_PLAYERGRAPHICSCOMPONENT_H
