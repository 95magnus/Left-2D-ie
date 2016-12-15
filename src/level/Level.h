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
typedef std::vector<TileMapRow> TileMap;
typedef std::vector<std::vector<sf::Sprite*>> SpriteMap;

class Level {
public:
    enum class Tile {
        DIRT,
        STONE
    };

    const unsigned int tileSize = 32;
    int levelWidth, levelHeight;

    Level(sf::Vector2u windowSize, int width, int height);
    Level(sf::Vector2u windowSize, const String fileName);
    virtual ~Level();

    void generateTestLevel();
    void loadFromFile(const std::string &filename);

    void update(float deltaTime);
    void draw(sf::RenderWindow &window);

    sf::Vector2i worldCoordToTileIndex(sf::Vector2f position);

    TileMap &getSurroundingTiles(sf::Vector2i index, int radius);

    void setMapOffset(sf::Vector2f offset);
    void translateMap(sf::Vector2f offset);

    TileMap& getTileMap() { return tiles; }

protected:
    const std::string levelDirectory = "resources/levels/";
    const std::string tilesheetFileName = "spritesheet_tiles.png";
    const unsigned int tileSpriteSize = 64;

    unsigned int xOffs = 0, yOffs = 0;
    bool levelLoaded = false;
    sf::Vector2u windowSize;

    std::map<Tile, sf::Texture*> textures;
    std::map<int, Tile> tileIDs;

    TileMap tiles;
    SpriteMap testMap;

    sf::Texture *tex;

    Level();

    TileBase* generateTile(Tile type, int x, int y);
};


#endif //LEFT2DIE_LEVEL_H
