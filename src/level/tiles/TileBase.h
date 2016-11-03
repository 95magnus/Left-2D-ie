#ifndef LEFT2DIE_TILEBASE_H
#define LEFT2DIE_TILEBASE_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

class TileBase {
public:
    virtual ~TileBase();

    void draw(sf::RenderWindow &window, int worldX, int worldY);

    void setTexture(sf::Texture &texture);

    virtual bool isSolid() const;

protected:
    sf::Texture* texture;
    sf::Sprite* sprite;

    sf::RectangleShape collisionBox;

    TileBase(int width, int height);
    TileBase(int width, int height, sf::Texture &texture);
};

#endif //LEFT2DIE_TILEBASE_H
