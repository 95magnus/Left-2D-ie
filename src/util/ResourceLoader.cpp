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

sf::Image& ResourceLoader::loadGuiImage(const String &filename) const{
    sf::Image* guiImage = new sf::Image();
    guiImage->loadFromFile(resourceDir + guiDir + filename);

    return *guiImage;
}

void ResourceLoader::loadGuiImage(sf::Image* image, const String &filename){
    image->loadFromFile(resourceDir + guiDir + filename);
}

sf::Texture& ResourceLoader::loadTexture(const String &fileName) const {
    sf::Texture* texture = new sf::Texture();
    texture->loadFromFile(resourceDir + textureDir + fileName);

    return *texture;
}

void ResourceLoader::loadTexture(sf::Texture* texture, const String &fileName) {
    texture->loadFromFile(resourceDir + textureDir + fileName);
}


sf::Texture& ResourceLoader::loadTextureFromSpritesheet(const String &fileName, int x, int y, int w, int h) const {
    sf::Texture *texture = new sf::Texture();
    texture->loadFromFile(resourceDir + tileDir + fileName, sf::IntRect(x * w, y * h, w, h));

    return *texture;
}

void ResourceLoader::loadTextureFromSpritesheet(sf::Texture* texture, const String &fileName, int x, int y, int w, int h) {
    texture->loadFromFile(resourceDir + tileDir + fileName, sf::IntRect(x * w, y * h, w, h));
}
