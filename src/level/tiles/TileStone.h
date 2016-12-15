#ifndef LEFT2DIE_TILESTONE_H
#define LEFT2DIE_TILESTONE_H

#include "TileBase.h"

class TileStone : public TileBase {
public:
    TileStone(unsigned int tileSize, int x, int y, sf::Texture &texture);
    virtual ~TileStone() {}

    bool isSolid() const;

protected:

};

#endif //LEFT2DIE_TILESTONE_H
