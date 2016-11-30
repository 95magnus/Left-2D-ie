#include "TileBase.h"

TileBase::TileBase(int width, int height) {
    collisionBox = sf::RectangleShape(sf::Vector2f(width, height));

    srand(time(NULL));
    int r = rand() % 255;
    int g = rand() % 255;
    int b = rand() % 255;

    sprite = new sf::Sprite();
    sprite->setColor(sf::Color(r, g, b));
}

TileBase::TileBase(int width, int height, sf::Texture &texture) {
    collisionBox = sf::RectangleShape(sf::Vector2f(width, height));

    sprite = new sf::Sprite(texture);

    sf::Vector2u texSize = texture.getSize();
    float scaleX = width / (float)texSize.x;
    float scaleY = height / (float)texSize.y;
    sprite->setScale(scaleX, scaleY);
}

TileBase::~TileBase() {
    delete sprite;
}

void TileBase::draw(sf::RenderWindow &window, int worldX, int worldY) {
    sprite->setPosition(worldX, worldY);
    window.draw(*sprite);
}

void TileBase::setTexture(sf::Texture& texture) {
    sprite->setTexture(texture);
}

bool TileBase::isSolid() const {
    return false;
}
