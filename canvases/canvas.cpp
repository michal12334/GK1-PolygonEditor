#include "canvas.h"

using namespace sf;

Canvas::Canvas(sf::Vector2i size, sf::Vector2f position) {
    this->size = size;
    this->position = position;
    image.create(size.x, size.y, Color::White);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void Canvas::setPixel(int x, int y, Color color) {
    if(x < 0 || y < 0 || x >= size.x || y >= size.y)
        return;

    image.setPixel(x, y, color);
}

Vector2f Canvas::getPosition() {
    return position;
}

void Canvas::updateTexture() {
    texture.loadFromImage(image);
}

void Canvas::draw(RenderTarget &target, RenderStates states) const {
    target.draw(sprite, states);
}
