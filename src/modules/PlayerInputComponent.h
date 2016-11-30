//
// Created by MortenSuvatne on 31.10.2016.
//

#ifndef LEFT2DIE_PLAYERINPUTCOMPONENT_H
#define LEFT2DIE_PLAYERINPUTCOMPONENT_H

#include "InputComponent.h"
#include "GameObject.h"

class PlayerInputComponent : public InputComponent{
public:
    // updates every frame
    virtual void update(GameObject& gameObject) {
        // TODO: Implement Player input Actions
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
            //Player and his hitbox goes left

        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
            //Player and his hitbox goes right

        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
            //Player and his hitbox goes up

        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
            //Player and his hitbox goes down

        }
    };
private:
    // Speed of the player
    static const int Player_acceleration = 1;
};

#endif //LEFT2DIE_PLAYERINPUTCOMPONENT_H
