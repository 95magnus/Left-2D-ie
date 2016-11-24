#include "TileStone.h"

TileStone::TileStone(unsigned int tileSize, sf::Texture &texture) : TileBase(tileSize, tileSize, texture) {

}

bool TileStone::isSolid() const {
    return true;
}