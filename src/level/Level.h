#ifndef LEFT2DIE_LEVEL_H
#define LEFT2DIE_LEVEL_H

#include <fstream>
#include <SFML/Graphics/View.hpp>
#include "tiles/TileBase.h"

class Level {
public:
    Level();
    virtual ~Level();

    void loadFromFile(const std::string &filename);

protected:
    const std::string levelDirectory = "resources/levels/";

    sf::View view;

    //TileBase tiles[5][5];
};


#endif //LEFT2DIE_LEVEL_H
