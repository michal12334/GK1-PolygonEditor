#include "rectangleButton.h"

using namespace sf;

RectangleButton::RectangleButton(Vector2f size, Vector2f position, Color color) :Button(size, position) {
    this->color = color;
    rectangle.setSize(size);
    rectangle.setPosition(position);
    rectangle.setFillColor(color);
}

void RectangleButton::setSize(Vector2f size) {
    Button::setSize(size);
    rectangle.setSize(size);
}

void RectangleButton::setPosition(Vector2f position) {
    Button::setPosition(position);
    rectangle.setPosition(position);
}

void RectangleButton::draw(RenderTarget &target, RenderStates states) const {
    target.draw(rectangle, states);
}
