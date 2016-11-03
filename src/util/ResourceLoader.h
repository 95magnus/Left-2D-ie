#ifndef LEFT2DIE_RESOURCELOADER_H
#define LEFT2DIE_RESOURCELOADER_H

#include <string>
#include <SFML/Graphics/Font.hpp>

typedef std::string String;

class ResourceLoader {
public:
    ResourceLoader(const String &directory);

    sf::Font& loadFont(const String &filename) const;
    void loadFont(sf::Font* font, const String &filename);

    sf::Texture& loadTexture(const String &fileName) const;
    void loadTexture(sf::Texture* texture, const String &fileName);

    sf::Texture& loadTextureFromSpritesheet(const String &fileName, int x, int y, int w, int h) const;
    void loadTextureFromSpritesheet(sf::Texture* texture, const String &fileName, int x, int y, int w, int h);

protected:
    const String fontDir = "fonts/";
    const String textureDir = "textures/";
    const String tileDir = "textures/tiles/";
    String resourceDir;
};

#endif //LEFT2DIE_RESOURCELOADER_H
