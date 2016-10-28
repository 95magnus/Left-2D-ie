#ifndef LEFT2DIE_TILEBASE_H
#define LEFT2DIE_TILEBASE_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class TileBase : public sf::Drawable {
public:
    virtual ~TileBase() {}

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) {
        target.draw(rect);
    }

    virtual bool isSolid() {
        return false;
    }

    void setTexture(sf::Texture *texture);

protected:
    unsigned int width, height;

    sf::Texture* texture;
    sf::RectangleShape rect;

    TileBase(unsigned int width, unsigned int height) : width(width), height(height) {}
};

#endif //LEFT2DIE_TILEBASE_H
