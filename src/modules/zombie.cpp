#include "zombie.h"

// Constructor
Zombie::Zombie(){
    health = 100;
    zom.setSize(sf::Vector2f(30,100));

    // Load Texture
    sf::Texture texture;
    texture.setSmooth(false);
    texture.setRepeated(false);
    if (!texture.loadFromFile("filnavn.bmp")){
        // Zombien blir grønn hvis bildet ikke blir lastet
        zom.setFillColor((sf::Color::Green));
    }
    else{
        zom.setTexture(&texture);
    }


}

// Deconstructor
Zombie::~Zombie(){

}

int Zombie::getHealt() const {
    return health;
}

void Zombie::setHealt(int health) {
    Zombie::health = health;

}

void Zombie::death() {
    // legge inn effekt for når zombien dør
}