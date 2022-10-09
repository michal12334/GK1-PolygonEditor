#include "editUsingMode.h"

using namespace sf;

EditUsingMode::EditUsingMode(Window* window, Canvas* canvas, PointDrawer* pointDrawer, LineDrawer* lineDrawer, PolygonsContainer* polygonsContainer) {
    this->window = window;
    this->canvas = canvas;
    this->pointDrawer = pointDrawer;
    this->lineDrawer = lineDrawer;
    this->polygonsContainer = polygonsContainer;
}

void EditUsingMode::update() {
    auto mousePositionOnCanvas = getMousePositionOnCanvas();
    if(mousePositionOnCanvas.x < 0 ||
        mousePositionOnCanvas.y < 0 ||
        mousePositionOnCanvas.x >= canvas->getSize().x ||
        mousePositionOnCanvas.y >= canvas->getSize().y)
            return;

    if(!isMouseLeftButtonPressed && Mouse::isButtonPressed(Mouse::Button::Left)) {
        isMouseLeftButtonPressed = true;
        if(points.size() >= 2 && isMouseOnFirstPoint(mousePositionOnCanvas)) {
            isPolygonBeingDrawn = false;
            polygonsContainer->addPolygon(points);
            points.clear();
        } else {
            points.push_back(mousePositionOnCanvas);
            isPolygonBeingDrawn = true;
        }
    } else if(!Mouse::isButtonPressed(Mouse::Button::Left)) {
        isMouseLeftButtonPressed = false;
    }
}

void EditUsingMode::draw() {
    if(points.size() == 0)
        return;

    for(int i = 0; i < points.size(); i++) {
        pointDrawer->draw(points[i]);
        if(i != points.size() - 1) {
            lineDrawer->draw(points[i], points[i + 1]);
        }
    }

    auto mousePositionOnCanvas = getMousePositionOnCanvas();
    pointDrawer->draw(mousePositionOnCanvas);
    lineDrawer->draw(points[points.size() - 1], mousePositionOnCanvas);
}

bool EditUsingMode::isMouseOnFirstPoint(Vector2i mousePosition) {
    if(points.size() == 0)
        return false;

    auto firstPointPosition = points[0];
    int d2 = (mousePosition.x - firstPointPosition.x) * (mousePosition.x - firstPointPosition.x) +
        (mousePosition.y - firstPointPosition.y) * (mousePosition.y - firstPointPosition.y);

    return d2 <= 6*6;
}

Vector2i EditUsingMode::getMousePositionOnCanvas() {
    auto canvasPosition = canvas->getPosition();
    auto mousePosition = Mouse::getPosition(*window);
    return Vector2i(mousePosition.x - canvasPosition.x, mousePosition.y - canvasPosition.y);
}
