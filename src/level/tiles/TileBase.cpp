#include "TileBase.h"

TileBase::TileBase(int tileSize, int x, int y) {
    this->tileSize = tileSize;
    this->worldX = x;
    this->worldY = y;
}

TileBase::TileBase(int tileSize, int x, int y, sf::Texture &texture) : TileBase(tileSize, x, y) {
    sprite = new sf::RectangleShape(sf::Vector2f(tileSize, tileSize));
    sprite->setTexture(&texture);
    sprite->setPosition(x, y);

    sf::Vector2u texSize = texture.getSize();
    float scaleX = tileSize / (float)texSize.x;
    float scaleY = tileSize / (float)texSize.y;
    //sprite->setScale(scaleX, scaleY);

    sprite->setOutlineColor(sf::Color::Magenta);
    sprite->setOutlineThickness(2);
}

TileBase::~TileBase() {
    delete sprite;
}

void TileBase::draw(sf::RenderWindow &window) {
    if (sprite)
        window.draw(*sprite);
}

void TileBase::setTexture(sf::Texture& texture) {
    sprite->setTexture(&texture);

    sf::Vector2u texSize = texture.getSize();
    float scaleX = tileSize / (float)texSize.x;
    float scaleY = tileSize / (float)texSize.y;
    sprite->setScale(scaleX, scaleY);
}

void TileBase::setMovements(int movements) {
    this->movements = movements;
    movementsUpdated = true;
}


bool TileBase::isSolid() const {
    return false;
}
