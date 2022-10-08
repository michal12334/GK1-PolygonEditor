#include "editUsingMode.h"

using namespace sf;

EditUsingMode::EditUsingMode(Window* window, Canvas* canvas) {
    this->window = window;
    this->canvas = canvas;
}

void EditUsingMode::update() {
    auto canvasPosition = canvas->getPosition();
    auto mousePosition = Mouse::getPosition(*window);
    auto mousePositionOnCanvas = Vector2i(mousePosition.x - canvasPosition.x, mousePosition.y - canvasPosition.y);

    if(!isMouseLeftButtonPressed && Mouse::isButtonPressed(Mouse::Button::Left)) {
        isMouseLeftButtonPressed = true;
        pointDrawer.draw(canvas, mousePositionOnCanvas);
    } else if(!Mouse::isButtonPressed(Mouse::Button::Left)) {
        isMouseLeftButtonPressed = false;
    }
}
