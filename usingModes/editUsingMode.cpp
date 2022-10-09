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
        if(points.size() >= 2 && isMouseOnFirstPoint(mousePositionOnCanvas)) {
            lineDrawer.draw(canvas, points[points.size() - 1], points[0]);
            isPolygonBeingDrawn = false;
            points.clear();
        } else {
            pointDrawer.draw(canvas, mousePositionOnCanvas);
            if(isPolygonBeingDrawn) {
                lineDrawer.draw(canvas, points[points.size() - 1], mousePositionOnCanvas);
            }
            points.push_back(mousePositionOnCanvas);
            isPolygonBeingDrawn = true;
        }
    } else if(!Mouse::isButtonPressed(Mouse::Button::Left)) {
        isMouseLeftButtonPressed = false;
    }
}

bool EditUsingMode::isMouseOnFirstPoint(Vector2i mousePosition) {
    if(points.size() == 0)
        return false;

    auto firstPointPosition = points[0];
    int d2 = (mousePosition.x - firstPointPosition.x) * (mousePosition.x - firstPointPosition.x) +
        (mousePosition.y - firstPointPosition.y) * (mousePosition.y - firstPointPosition.y);

    return d2 <= 6*6;
}
