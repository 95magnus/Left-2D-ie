#include "TileStone.h"
#include "../../util/ResourceLoader.h"

TileStone::TileStone(unsigned int tileSize, int x, int y, sf::Texture &texture) : TileBase(tileSize, x, y, texture) {

}

bool TileStone::isSolid() const {
    return true;
}
