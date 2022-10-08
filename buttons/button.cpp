#include "button.h"

using namespace sf;

Button::Button(Vector2f size, Vector2f position) {
    this->size = size;
    this->position = position;
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

void Button::setSize(sf::Vector2f size) {
    this->size = size;
}

void Button::setPosition(sf::Vector2f position) {
    this->position = position;
}
