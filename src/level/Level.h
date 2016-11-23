#ifndef LEFT2DIE_LEVEL_H
#define LEFT2DIE_LEVEL_H

#include <sstream>
#include <iostream>
#include <fstream>
#include <map>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "tiles/TileStone.h"
#include "../util/ResourceLoader.h"

class TileBase;

typedef std::vector<TileBase*> TileMapRow;
typedef std::vector<std::vector<TileBase*>> TileMap;
typedef std::vector<std::vector<sf::Sprite*>> SpriteMap;

class Level {
public:
    enum class Tile {
        DIRT,
        STONE
    };

    Level(int width, int height);
    Level(const String fileName);
    virtual ~Level();

    void initTiles();
    void generateTestLevel();
    void loadFromFile(const std::string &filename);

    void update(float deltaTime);
    void draw(sf::RenderWindow &window);

    int tileCoordToPixel();

    sf::View &getView() { return *view; }

protected:
    const std::string levelDirectory = "resources/levels/";
    const std::string tilesheetFileName = "spritesheet_tiles.png";
    const unsigned int tileSize = 32, tileSpriteSize = 64;

    unsigned int width, height;
    bool levelLoaded = false;

    Level();

    sf::View* view;

    std::map<Tile, TileBase*> tileRegistry;
    std::map<int, Tile> tileIDs;

    TileMap tiles;
    SpriteMap testMap;

    sf::Texture *tex;
};


#endif //LEFT2DIE_LEVEL_H
