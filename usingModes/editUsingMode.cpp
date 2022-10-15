#include "editUsingMode.h"

using namespace sf;

EditUsingMode::EditUsingMode(Window* window, Canvas* canvas, PointDrawer* pointDrawer, LineDrawer* lineDrawer, PolygonsContainer* polygonsContainer, PointTouchDetector* pointTouchDetector) {
    this->window = window;
    this->canvas = canvas;
    this->pointDrawer = pointDrawer;
    this->lineDrawer = lineDrawer;
    this->polygonsContainer = polygonsContainer;
    this->pointTouchDetector = pointTouchDetector;
    
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
            auto currentTouchedPointData = pointTouchDetector->getTouchedPoint(mousePositionOnCanvas);
            if(currentTouchedPointData == nullptr) {
                polygonCreator->restart();
                isPolygonBeingDrawn = true;
                polygonCreator->update();
            } else {
                touchedPointData = currentTouchedPointData;
                pointDragAndDropper = new PointDragAndDropper(touchedPointData, lineDrawer, pointDrawer, polygonsContainer);
            }
        }
    } else if(!Mouse::isButtonPressed(Mouse::Button::Left)) {
        isMouseLeftButtonPressed = false;
        if(pointDragAndDropper != nullptr) {
            pointDragAndDropper->finish();
            delete pointDragAndDropper;
            delete touchedPointData;
            pointDragAndDropper = nullptr;
            touchedPointData = nullptr;
        }
    } else {
        if(pointDragAndDropper != nullptr) {
            pointDragAndDropper->update(mousePositionOnCanvas);
        }
    }
}

void EditUsingMode::draw() {
    if(pointDragAndDropper != nullptr)
        pointDragAndDropper->draw();
    else if(isPolygonBeingDrawn)
        polygonCreator->draw();
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
