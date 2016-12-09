//
// Created by MortenSuvatne on 30.10.2016.
//

#ifndef LEFT2DIE_PHYSICSCOMPONENT_H
#define LEFT2DIE_PHYSICSCOMPONENT_H


class PhysicsComponent {
public:
    virtual ~PhysicsComponent() {}
    virtual void update(GameObject& obj, World& world) = 0;
};


#endif //LEFT2DIE_PHYSICSCOMPONENT_H
