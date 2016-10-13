#include "ResourceLoader.h"

ResourceLoader::ResourceLoader(const String &directory) {
    this->resourceDir = directory;
}

sf::Font& ResourceLoader::loadFont(const String &filename) const {
    sf::Font* font = new sf::Font();
    font->loadFromFile(resourceDir + fontDir + filename);

    return *font;
}

void ResourceLoader::loadFont(sf::Font* font, const String &filename) {
    font->loadFromFile(resourceDir + fontDir + filename);
}

sf::Texture& ResourceLoader::loadTexture(const String &fileName) const {
    sf::Texture* texture = new sf::Texture();
    texture->loadFromFile(resourceDir + textureDir + fileName);

    return *texture;
}

void ResourceLoader::loadTexture(sf::Texture* texture, const String &fileName) {
    texture->loadFromFile(resourceDir + textureDir + fileName);
}
