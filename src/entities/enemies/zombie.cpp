#include "zombie.h"

// Constructor
Zombie::Zombie(){
    health = 100;
    speed = 25;
    armor = 0;
    zom.setSize(sf::Vector2f(30,100));

    // Load Texture
    sf::Texture texture;
    texture.setSmooth(false);
    texture.setRepeated(false);
    if (!texture.loadFromFile("resources/character_models/zombie_v1.0.png")){
        // Zombien blir grønn hvis bildet ikke blir lastet
        zom.setFillColor((sf::Color::Green));
    }
    else{
        zom.setTexture(&texture);
    }

    // Hitboxen blir like bred og høy som zombien
    hitbox.setSize(sf::Vector2f(zom.getSize().x, zom.getSize().y));
    // Hitboxen ligger rundt karakterens føtter.
    hitbox.setPosition(zom.getPosition().x, zom.getPosition().y + zom.getSize().y - hitbox.getSize().y);


}


// Action functions
void Zombie::moveUp(float dt) {
    sprite.move(0.f, speed * dt * -1);
    hitbox.move(0.f, speed * dt * -1);
}

void Zombie::moveDown(float dt) {
    sprite.move(0.f, speed * dt);
    hitbox.move(0.f, speed * dt);
}

void Zombie::moveRight(float dt) {
    sprite.move(speed * dt, 0.f);
    hitbox.move(speed * dt, 0.f);
}

void Zombie::moveLeft(float dt) {
    sprite.move(speed * dt * -1, 0.f);
    hitbox.move(speed * dt * -1, 0.f);
}

// Deconstructor
Zombie::~Zombie(){

}

int Zombie::getHealth() const {
    return health;
}

void Zombie::setHealth(int health) {
    Zombie::health = health;
}

int Zombie::getSpeed() const {
    return speed;
}

void Zombie::setSpeed(int speed) {
    Zombie::speed = speed;
}

void Zombie::hit() {
    //life loss at hit
    Zombie::setHealth(Zombie::getHealth() - 5);
    //hit music effect
    SBuffer.loadFromFile("damage_hit1.wav");
    sound.setBuffer(SBuffer);
    sound.play();
}

void Zombie::death() {
    //Death Sound effect.
    SBuffer.loadFromFile("resources/sound_effect/wilhelm_scream.wav");
    sound.setBuffer(SBuffer);
    sound.play();

    // TODO: legge inn animasjon for når zombien dør
}