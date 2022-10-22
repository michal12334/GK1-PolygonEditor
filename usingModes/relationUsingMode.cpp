#include "relationUsingMode.h"

using namespace sf;

RelationUsingMode::RelationUsingMode(
    Window* window,
    Canvas* canvas,
    EdgeTouchDetector* edgeTouchDetector,
    PolygonsContainer* polygonsContainer
) {
    this->window = window;
    this->canvas = canvas;
    this->edgeTouchDetector = edgeTouchDetector;
    this->polygonsContainer = polygonsContainer;
}

void RelationUsingMode::update() {
    auto mousePositionOnCanvas = getMousePositionOnCanvas();
    if(!isMouseOnCanvas(mousePositionOnCanvas))
        return;

    polygonsContainer->clearHighlight();
    auto touchedEdgeData = edgeTouchDetector->getTouchedEdge(mousePositionOnCanvas);
    if(touchedEdgeData != nullptr) {
        polygonsContainer->setHighlighten(touchedEdgeData);
    } else {
        return;
    }

    if(!isMouseLeftButtonPressed && Mouse::isButtonPressed(Mouse::Button::Left)) {
        isMouseLeftButtonPressed = true;
        polygonsContainer->setEdgeLength(touchedEdgeData);
    } else if(!Mouse::isButtonPressed(Mouse::Button::Left)) {
        isMouseLeftButtonPressed = false;
    }

    if(touchedEdgeData != nullptr)
        delete touchedEdgeData;
}

void RelationUsingMode::draw() {
}

Vector2i RelationUsingMode::getMousePositionOnCanvas() {
    auto canvasPosition = canvas->getPosition();
    auto mousePosition = Mouse::getPosition(*window);
    return Vector2i(mousePosition.x - canvasPosition.x, mousePosition.y - canvasPosition.y);
}

bool RelationUsingMode::isMouseOnCanvas(Vector2i mousePositionOnCanvas) {
    return mousePositionOnCanvas.x >= 0 &&
        mousePositionOnCanvas.y >= 0 &&
        mousePositionOnCanvas.x < canvas->getSize().x &&
        mousePositionOnCanvas.y < canvas->getSize().y;
}
