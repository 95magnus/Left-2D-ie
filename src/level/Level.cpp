#include "Level.h"

Level::Level() {
    initTiles();

    view = new sf::View();
}

Level::Level(sf::Vector2u windowSize, int width, int height) : Level() {
    this->windowSize = windowSize;
    this->width = width;
    this->height = height;

    generateTestLevel();
}

Level::Level(sf::Vector2u windowSize, const String fileName) : Level() {
    this->windowSize = windowSize;

    loadFromFile(fileName);
}

Level::~Level() {
    delete view;

    for (auto &row : testMap)
        for (auto &tile : row)
            delete tile;

    // delete tex;

    for (auto &tile : tileRegistry)
        delete tile.second;
}

void Level::initTiles() {
    ResourceLoader loader("resources/");

    tileRegistry[Tile::DIRT] =
            new TileStone(tileSize, loader.loadTextureFromSpritesheet(tilesheetFileName, 0, 0, tileSpriteSize, tileSpriteSize));
    tileRegistry[Tile::STONE] =
            new TileStone(tileSize, loader.loadTextureFromSpritesheet(tilesheetFileName, 0, 2, tileSpriteSize, tileSpriteSize));

    tileIDs[0] = Tile::DIRT;
    tileIDs[1] = Tile::STONE;
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
    for (int y = 0; y < height; y++) {
        std::vector<sf::Sprite*> row;

        for (int x = 0; x < width; x++) {
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

    width = metadata[0];
    height = metadata[1];

    int rowTiles = 0;

    // Read level tile data line by line
    while(std::getline(file, line)) {
        if (line == "")
            continue;

        std::stringstream ss;
        ss.str(line);

        String strTileID;
        TileMapRow row;

        // Spilt tileIDs by delimiter ' '
        while (std::getline(ss, strTileID, ' ')) {
            int tileID;
            std::istringstream(strTileID) >> tileID;

            TileBase* tile;

            // Check if tileID is valid (contains at least 1 entry)
            if (tileIDs.count(tileID)) {
                // Look up tile object from ID
                tile = tileRegistry[tileIDs[tileID]];   // Valid ID
            } else {
                tile = tileRegistry[Tile::DIRT];        // Invalid ID
            }

            row.push_back(tile);
        }

        if (width != row.size()) {
            std::cerr << "Level loading error in file \"" << filename << "\"\n"
                      << "Level width " << row.size() << " found at row " << rowTiles
                      << "\nExpected: " << width;
            exit(1);
        }

        tiles.push_back(row);
        rowTiles++;
    }

    if (height != tiles.size()) {
        std::cerr << "Level loading error in file \"" << filename << "\"\n"
                  << "Level height " << tiles.size() << " found"
                  << "\nExpected: " << height;
        exit(1);
    }

    levelLoaded = true;
}

void Level::update(float deltaTime) {

}

void Level::draw(sf::RenderWindow &window) {
    if (!levelLoaded)
        return;




    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            tiles[y][x]->draw(window, x * tileSize - xOffs, y * tileSize - yOffs);
        }
    }
}

void Level::drawTiles(sf::RenderWindow &window, sf::Vector2f worldCoordCenter) {
    if (!levelLoaded)
        return;

    // Find bounds of viewport
    int worldMinX = (int)(worldCoordCenter.x - (windowSize.x/2));
    int worldMinY = (int)(worldCoordCenter.y - (windowSize.y/2));
    int worldMaxX = (int)(worldCoordCenter.x + (windowSize.x/2));
    int worldMaxY = (int)(worldCoordCenter.y + (windowSize.y/2));

    // Find tile bounds within viewport
    int tileIndexMinX = worldMinX / (int)tileSize;
    int tileIndexMinY = worldMinY / (int)tileSize;
    int tileIndexMaxX = worldMaxX / (int)tileSize;
    int tileIndexMaxY = worldMaxY / (int)tileSize;

    int xScreen = 0, yScreen = 0;


    // Draw tiles within viewport
    for (int y = tileIndexMinY; y < tileIndexMaxY; y++) {
        if (y < 0 || y >= height)
            continue;

        yScreen += tileSize;

        for (int x = tileIndexMinX; x < tileIndexMaxX; x++) {
            if (x < 0 || x >= width)
                continue;

            xScreen += tileSize;

            tiles[y][x]->draw(window, xScreen, yScreen);
        }
    }
}

void Level::setMapOffset(sf::Vector2f offset) {
    xOffs = offset.x;
    yOffs = offset.y;
}

void Level::translateMap(sf::Vector2f offset) {
    //if (xOffs + offset.x > 0 && xOffs + offset.x < windowSize.x)
    xOffs += offset.x;

    yOffs += offset.y;
}

sf::Vector2i Level::worldCoordToTile(sf::Vector2f position) {
    return sf::Vector2i((position.x - xOffs) / tileSize, (position.y - yOffs) / tileSize);
}



