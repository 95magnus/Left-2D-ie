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

    sf::Image& loadGuiImage(const String &fileName) const;
    void loadGuiImage(sf::Image* image, const String &fileName);

protected:
    const String fontDir = "fonts/";
    const String textureDir = "textures/";
    const String guiDir = "gui/";
    String resourceDir;
};

#endif //LEFT2DIE_RESOURCELOADER_H
