#include "StateShop.h"

StateShop::StateShop(Game *game) : StateBase(game){
    initShopGui();
}

StateShop::~StateShop() {

}

void StateShop::pause() {
    desktop->RemoveAll();
}

void StateShop::resume() {
    StateBase::resume();
    initShopGui();
}

void StateShop::update(float deltaTime) {

}

void StateShop::draw(sf::RenderWindow &window) {
    sf::Text title("SHOP", game->getFont(), 140);

    title.setColor(sf::Color::Red);
    title.setPosition(275, 50);

    game->getWindow().draw(title);
}

void StateShop::initShopGui() {
    desktop->SetProperty("*", "FontName", "resources/fonts/feast-of-flesh-bb.italic.ttf");

    nextButton = sfg::Button::Create();
    createShopButtonImage(nextButton, "right_arrow.png");
    nextButton->SetPosition(sf::Vector2f(0.f, 0.f));
    nextButton->SetRequisition(sf::Vector2f(0.f,0.f));

    desktop->Add(nextButton);
}

void StateShop::createImage(sfg::Image::Ptr image, const String &filename) {
    auto temp = new sf::Image;
    if(temp->loadFromFile(filename)){
        image->SetImage(*temp);
    }
}
