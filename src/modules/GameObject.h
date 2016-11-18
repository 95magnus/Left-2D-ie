//
// Created by MortenSuvatne on 30.10.2016.
//

#ifndef LEFT2DIE_GAMEOBJECT_H
#define LEFT2DIE_GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include "InputComponent.h"
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"
#include "PlayerInputComponent.h"
#include "PlayerGraphicsComponent.h"
#include "PlayerPhysicsComponent.h"
#include "ZombieGraphicsComponent.h"
#include "ZombiePhysicsComponent.h"
#include "AIComponent.h"


class GameObject {
public:
    int velocity;
    int x, y;

    GameObject(InputComponent& input,
               PhysicsComponent physics,
               GraphicsComponent graphics): input_(input), physics_(physics), graphics_(graphics)
    {}

    void update(World& world, Graphics& graphics) {
        input_->update(*this);
        physics_->update(*this, world);
        graphics_->update(*this, graphics);
    }

    GameObject* createPlayer(){
        return new GameObject(new PlayerInputComponent(), new PlayerPhysicsComponent(), new PlayerGraphicsComponent());
    }

    GameObject* createZombie(){
        return new GameObject(new AIComponent(), new ZombiePhysicsComponent(), new ZombieGraphicsComponent());
    }
private:
    InputComponent* input_;
    PhysicsComponent* physics_;
    GraphicsComponent* graphics_;
};


#endif //LEFT2DIE_GAMEOBJECT_H
