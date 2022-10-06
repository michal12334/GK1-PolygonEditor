#include "upperPanel.h"

using namespace sf;

UpperPanel::UpperPanel(Vector2f size, Vector2f position) {
    this->size = size;
    this->position = position;
    color = sf::Color::Cyan;
    rectangle.setSize(size);
    rectangle.setPosition(position);
    rectangle.setFillColor(color);
}

void UpperPanel::draw(RenderTarget &target, RenderStates states) const {
    target.draw(rectangle, states);
}
