#include "Button.h"

Button::Button(const unsigned int width, const unsigned int height, const String &title){
    buttonSelect = sfg::Button::Create();
    sf::Image image;
    ResourceLoader loader("resources/");
    loader.loadGuiImage("button.png");
    sfg::Image::Ptr selectImageSFG = sfg::Image::Create(image);
    buttonSelect->SetImage(selectImageSFG);
    buttonSelect->SetId("button.png");
    buttonSelect->GetSignal(sfg::Widget::OnLeftClick).Connect(&Button::ButtonClicked);

    this->width = width;
    this->height = height;
    this->title = title;
}

Button::~Button(){
    // Delete...
}

void Button::ButtonClicked() {
    // Actions like changing states
    // In-game: shop and change equipments
}

void Button::TypeClicked() {

}

void Button::Draw() {

}

Button::Button() {}

