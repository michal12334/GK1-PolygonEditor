#include "editUsingMode.h"

using namespace sf;

EditUsingMode::EditUsingMode(Window* window, Canvas* canvas, PointDrawer* pointDrawer, LineDrawer* lineDrawer, PolygonsContainer* polygonsContainer) {
    this->window = window;
    this->canvas = canvas;
    this->pointDrawer = pointDrawer;
    this->lineDrawer = lineDrawer;
    this->polygonsContainer = polygonsContainer;
    
    polygonCreator = new PolygonCreator(pointDrawer, lineDrawer, canvas, window);
}

EditUsingMode::~EditUsingMode() {
    delete polygonCreator;
}

void EditUsingMode::update() {
    auto mousePositionOnCanvas = getMousePositionOnCanvas();
    if(!isMouseOnCanvas(mousePositionOnCanvas))
        return;

    if(!isMouseLeftButtonPressed && Mouse::isButtonPressed(Mouse::Button::Left)) {
        isMouseLeftButtonPressed = true;
        if(isPolygonBeingDrawn) {
            polygonCreator->update();

            if(polygonCreator->isEnd()) {
                polygonsContainer->addPolygon(polygonCreator->getPoints());
                isPolygonBeingDrawn = false;
            }
        } else {
            polygonCreator->restart();
            isPolygonBeingDrawn = true;
            polygonCreator->update();
        }
    } else if(!Mouse::isButtonPressed(Mouse::Button::Left)) {
        isMouseLeftButtonPressed = false;
    }
}

void EditUsingMode::draw() {
    polygonCreator->draw();
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

bool EditUsingMode::isMouseOnCanvas(Vector2i mousePositionOnCanvas) {
    return mousePositionOnCanvas.x >= 0 &&
        mousePositionOnCanvas.y >= 0 &&
        mousePositionOnCanvas.x < canvas->getSize().x &&
        mousePositionOnCanvas.y < canvas->getSize().y;
}
