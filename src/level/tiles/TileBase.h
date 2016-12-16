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

    virtual void draw(sf::RenderWindow &window);

    void setTexture(sf::Texture &texture);

    virtual bool isSolid() const;

    sf::FloatRect getBounds() { return sprite->getGlobalBounds(); }
    sf::Vector2i getWorldPos() { return sf::Vector2i(worldX, worldY); }

    void setMovements(int movements);
    int getMovements() { return movements; }
    void incrementCost() { movements += 3; }

    void resetMovements() { movementsUpdated = false; }
    bool isMovementsUpdated() { return movementsUpdated; }

protected:
    int worldX, worldY, tileSize;

    // Number of movements to player
    int movements = 0;
    bool movementsUpdated = false;

    sf::Texture* texture;
    sf::RectangleShape* sprite;

    TileBase(int tileSize, int x, int y);
    TileBase(int tileSize, int x, int y, sf::Texture &texture);
};

#endif //LEFT2DIE_TILEBASE_H
