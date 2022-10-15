#include "button.h"

using namespace sf;

Button::Button(Vector2f size, Vector2f position, int borderSize) {
    this->size = size;
    this->position = position;
    isActive = false;
    rectangle.setSize(size);
    rectangle.setPosition(position);
    rectangle.setFillColor(Color::Red);
    borderLeft.setSize(Vector2f(borderSize, size.y));
    borderLeft.setPosition(position);
    borderLeft.setFillColor(Color::Black);
    borderRight.setSize(Vector2f(borderSize, size.y));
    borderRight.setPosition(Vector2f(getRight() - borderSize, position.y));
    borderRight.setFillColor(Color::Black);
    borderBottom.setSize(Vector2f(size.x, borderSize));
    borderBottom.setPosition(Vector2f(position.x, getBottom() - borderSize));
    borderBottom.setFillColor(Color::Black);
    borderUp.setSize(Vector2f(size.x, borderSize));
    borderUp.setPosition(position);
    borderUp.setFillColor(Color::Black);
}

bool Button::isClicked(Window* window) {
    auto mousePosition = Mouse::getPosition(*window);
    return mousePosition.x >= getLeft() &&
        mousePosition.x <= getRight() &&
        mousePosition.y >= getUp() &&
        mousePosition.y <= getBottom();
}

float Button::getLeft() {
    return position.x;
}

float Button::getRight() {
    return position.x + size.x;
}

float Button::getUp() {
    return position.y;
}

float Button::getBottom() {
    return position.y + size.y;
}

void Button::setActive(bool isActive) {
    this->isActive = isActive;
}

void Button::draw(RenderTarget &target, RenderStates states) const {
    target.draw(rectangle, states);
    if(isActive) {
        target.draw(borderLeft, states);
        target.draw(borderRight, states);
        target.draw(borderUp, states);
        target.draw(borderBottom, states);
    }
}
