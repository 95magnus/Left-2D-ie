#include "Level.h"
#include "tiles/TileDirt.h"

Level::Level() {
    ResourceLoader loader("resources/");

    textures[Tile::DIRT] = &loader.loadTextureFromSpritesheet(tilesheetFileName, 0, 0, tileSpriteSize, tileSpriteSize);
    textures[Tile::STONE] = &loader.loadTextureFromSpritesheet(tilesheetFileName, 0, 2, tileSpriteSize, tileSpriteSize);

    tileIDs[0] = Tile::DIRT;
    tileIDs[1] = Tile::STONE;
}

Level::Level(sf::Vector2u windowSize, int width, int height) : Level() {
    this->windowSize = windowSize;
    this->levelWidth = width;
    this->levelHeight = height;

    generateTestLevel();
}

Level::Level(sf::Vector2u windowSize, const String fileName) : Level() {
    this->windowSize = windowSize;

    loadFromFile(fileName);
}

Level::~Level() {
    for (auto &row : testMap)
        for (auto &tile : row)
            delete tile;

    for (auto &tile : textures)
        delete tile.second;
}

void Level::generateTestLevel() {
    tex = new sf::Texture();
    tex->create(tileSize, tileSize);
    sf::Uint8* pixels = new sf::Uint8[tileSize * tileSize * 4];
    for (int i = 0; i < tileSize * tileSize * 4; i++){
        pixels[i] = 0x00;
    }
    tex->update(pixels);

    srand(time(NULL));
    for (int y = 0; y < levelHeight; y++) {
        std::vector<sf::Sprite*> row;

        for (int x = 0; x < levelWidth; x++) {
            sf::Sprite *sprite = new sf::Sprite();
            sprite->setTexture(*tex);
            sprite->setPosition(x * tileSize, y * tileSize);

            int r = rand() % 255;
            int g = rand() % 255;
            int b = rand() % 255;

            sprite->setColor(sf::Color(r, g, b));

            row.push_back(sprite);
        }

        testMap.push_back(row);
    }

    levelLoaded = true;
}

/***
 * Loads a .l2d level file from resources/levels/ directory. Level file consists of a grid
 * of IDs seperated by a space. Level must be a complete rectangle.
 * E.g.
 *
 * ---testLevel.l2d---
 * 7 6
 * 0 0 0 0 0 0 0
 * 0 1 1 1 1 1 0
 * 0 1 1 1 1 1 0
 * 0 1 1 1 1 1 0
 * 0 1 1 1 1 1 0
 * 0 0 0 0 0 0 0
 * -------------------
 *
 * @param filename .l2d level file name
 */
void Level::loadFromFile(const std::string &filename) {
    std::ifstream file(levelDirectory + filename);
    String line;

    // Read metadata line
    getline(file, line);

    String strValue;
    std::vector<int> metadata;

    // Spilt metadata by delimiter ' '
    std::stringstream meta;
    meta.str(line);
    while(std::getline(meta, strValue, ' ')) {
        int value;
        std::istringstream(strValue) >> value;

        metadata.push_back(value);
    }

    levelWidth = metadata[0];
    levelHeight = metadata[1];

    int xIndex = 0, yIndex = 0;

    // Read level tile data line by line
    while(std::getline(file, line)) {
        if (line == "")
            continue;

        std::stringstream ss;
        ss.str(line);

        String strTileID;
        TileMapRow row;

        xIndex = 0;
        // Spilt tileIDs by delimiter ' '
        while (std::getline(ss, strTileID, ' ')) {
            int tileID;
            std::istringstream(strTileID) >> tileID;

            // Check if tileID is valid (map contains at least 1 entry)
            if (tileIDs.count(tileID)) {
                row.push_back(generateTile(tileIDs[tileID], xIndex * tileSize, yIndex * tileSize));   // Valid ID
            } else {
                row.push_back(generateTile(Tile::DIRT, xIndex * tileSize, yIndex * tileSize));        // Invalid ID
            }

            xIndex++;
        }

        if (levelWidth != row.size()) {
            std::cerr << "Level loading error in file \"" << filename << "\"\n"
                      << "Level levelWidth " << row.size() << " found at row " << yIndex
                      << "\nExpected: " << levelWidth;
            exit(1);
        }

        tiles.push_back(row);
        yIndex++;
    }

    if (levelHeight != tiles.size()) {
        std::cerr << "Level loading error in file \"" << filename << "\"\n"
                  << "Level levelHeight " << tiles.size() << " found"
                  << "\nExpected: " << levelHeight;
        exit(1);
    }

    levelLoaded = true;
}

void Level::update(float deltaTime) {

}

void Level::draw(sf::RenderWindow &window) {
    if (!levelLoaded)
        return;

    for (unsigned int y = 0; y < levelHeight; y++) {
        for (unsigned int x = 0; x < levelWidth; x++) {
            tiles[y][x]->draw(window);
        }
    }
}

void Level::setMapOffset(sf::Vector2f offset) {
    xOffs = offset.x;
    yOffs = offset.y;
}

void Level::translateMap(sf::Vector2f offset) {
    xOffs += offset.x;
    yOffs += offset.y;
}

sf::Vector2i Level::worldCoordToTileIndex(sf::Vector2f position) {
    if (position.x >= levelWidth * tileSize
        || position.x < 0
        || position.y >= levelHeight * tileSize
        || position.y < 0) {
        return sf::Vector2i(-1,-1);
    }

    return sf::Vector2i((int)(position.x) / tileSize, (int)(position.y) / tileSize);
}

TileMap &Level::getSurroundingTiles(sf::Vector2i index, int radius) {
    TileMap* tileSection = new TileMap();

    int xMin = std::max(0, index.x - radius);
    int xMax = std::min(levelWidth - 1, index.x + radius);
    int yMin = std::max(0, index.y - radius);
    int yMax = std::min(levelHeight - 1, index.y + radius);

    for (int y = yMin; y <= yMax; y++) {
        TileMapRow* row = new TileMapRow();

        for (int x = xMin; x <= xMax; x++) {
            row->push_back(tiles[y][x]);
        }

        tileSection->push_back(*row);
    }

    return *tileSection;
}

TileBase* Level::generateTile(Level::Tile type, int x, int y) {
    switch(type) {
        case Tile::DIRT:
            return new TileDirt(tileSize, x, y, *textures[Tile::DIRT]);
        case Tile::STONE:
            return new TileStone(tileSize, x, y, *textures[Tile::STONE]);
        default:
            return nullptr;
    }
}



