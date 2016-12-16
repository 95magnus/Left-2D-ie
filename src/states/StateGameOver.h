#ifndef LEFT2DIE_STATEGAMEOVER_H
#define LEFT2DIE_STATEGAMEOVER_H


#include "../level/tiles/TileBase.h"
#include "../Game.h"

class StateGameOver : public StateBase {
public:
    StateGameOver(Game* game);
    virtual ~StateGameOver();

    void update(float deltaTime);
    void draw(sf::RenderWindow &window);

    void setScore(int score);

protected:
    sf::Text gameOverTitle, score;

    sf::RectangleShape graveStone;
};


#endif //LEFT2DIE_STATEGAMEOVER_H
