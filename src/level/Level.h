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

    Level(sf::Vector2u windowSize, int width, int height);
    Level(sf::Vector2u windowSize, const String fileName);
    virtual ~Level();

    void initTiles();
    void generateTestLevel();
    void loadFromFile(const std::string &filename);

    sf::Vector2f checkCollision();

    void update(float deltaTime);
    void draw(sf::RenderWindow &window);

    void drawTiles(sf::RenderWindow &window, sf::Vector2f worldCoordCenter);

    int tileCoordToPixel();
    sf::Vector2i worldCoordToTile(sf::Vector2f position);

    void setMapOffset(sf::Vector2f offset);
    void translateMap(sf::Vector2f offset);

    sf::View &getView() { return *view; }

protected:
    const std::string levelDirectory = "resources/levels/";
    const std::string tilesheetFileName = "spritesheet_tiles.png";
    const unsigned int tileSize = 32, tileSpriteSize = 64;

    unsigned int width, height, xOffs = 0, yOffs = 0;
    bool levelLoaded = false;
    sf::Vector2u windowSize;

    Level();

    sf::View* view;

    std::map<Tile, TileBase*> tileRegistry;
    std::map<int, Tile> tileIDs;

    TileMap tiles;
    SpriteMap testMap;

    sf::Texture *tex;
};


#endif //LEFT2DIE_LEVEL_H
