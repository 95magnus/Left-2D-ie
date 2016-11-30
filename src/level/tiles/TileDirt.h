#ifndef LEFT2DIE_TILEDIRT_H
#define LEFT2DIE_TILEDIRT_H

#include "TileBase.h"

class TileDirt : public TileBase {
public:
    TileDirt(unsigned int tileSize, sf::Texture &texture);
    virtual ~TileDirt() {}

protected:

};

#endif //LEFT2DIE_TILEDIRT_H
