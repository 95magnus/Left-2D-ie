#include "StateShop.h"

StateShop::StateShop(Game *game) : StateBase(game){
    initShopGui();
}

StateShop::~StateShop() {

}

void StateShop::update(float deltaTime) {

}

void StateShop::pause() {
    desktop->RemoveAll();
}

void StateShop::resume() {
    StateBase::resume();
    initShopGui();
}

void StateShop::draw() {
    sf::Text title("Left[2D]ie", game->getFont(), 140);
    title.setColor(sf::Color::Red);
    title.setPosition(275, 50);

    game->getWindow().draw(title);
}

void StateShop::initShopGui() {

}
