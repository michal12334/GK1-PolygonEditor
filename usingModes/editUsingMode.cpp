#include "editUsingMode.h"

using namespace sf;

EditUsingMode::EditUsingMode(
    Window* window,
    Canvas* canvas,
    PointDrawer* pointDrawer,
    LineDrawer* lineDrawer,
    PolygonsContainer* polygonsContainer,
    PointTouchDetector* pointTouchDetector,
    EdgeTouchDetector* edgeTouchDetector)
{
    this->window = window;
    this->canvas = canvas;
    this->pointDrawer = pointDrawer;
    this->lineDrawer = lineDrawer;
    this->polygonsContainer = polygonsContainer;
    this->pointTouchDetector = pointTouchDetector;
    this->edgeTouchDetector = edgeTouchDetector;
    
    polygonCreator = new PolygonCreator(pointDrawer, lineDrawer, canvas, window);
}

EditUsingMode::~EditUsingMode() {
    delete polygonCreator;
}

void EditUsingMode::update() {
    auto mousePositionOnCanvas = getMousePositionOnCanvas();
    if(!isMouseOnCanvas(mousePositionOnCanvas))
        return;

    updateHighlight(mousePositionOnCanvas);

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
                auto currentTouchedEdgeData = edgeTouchDetector->getTouchedEdge(mousePositionOnCanvas);
                if(currentTouchedEdgeData == nullptr) {
                    polygonCreator->restart();
                    isPolygonBeingDrawn = true;
                    polygonCreator->update();
                } else {
                    touchedEdgeData = currentTouchedEdgeData;
                    edgeDragAndDropper = new EdgeDragAndDropper(touchedEdgeData, lineDrawer, pointDrawer, polygonsContainer, mousePositionOnCanvas);
                }
            } else {
                touchedPointData = currentTouchedPointData;
                pointDragAndDropper = new PointDragAndDropper(touchedPointData, lineDrawer, pointDrawer, polygonsContainer, mousePositionOnCanvas);
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
        } else if(edgeDragAndDropper != nullptr) {
            edgeDragAndDropper->finish();
            delete edgeDragAndDropper;
            delete touchedEdgeData;
            edgeDragAndDropper = nullptr;
            touchedEdgeData = nullptr;
        }
    } else {
        if(pointDragAndDropper != nullptr) {
            pointDragAndDropper->update(mousePositionOnCanvas);
        } else if(edgeDragAndDropper != nullptr) {
            edgeDragAndDropper->update(mousePositionOnCanvas);
        }
    }
}

void EditUsingMode::draw() {
    if(pointDragAndDropper != nullptr)
        pointDragAndDropper->draw();
    else if(edgeDragAndDropper != nullptr)
        edgeDragAndDropper->draw();
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

void EditUsingMode::updateHighlight(Vector2i mousePositionOnCanvas) {
    polygonsContainer->clearHighlight();
    auto currentTouchedPointData = pointTouchDetector->getTouchedPoint(mousePositionOnCanvas);
    auto currentTouchedEdgeData = edgeTouchDetector->getTouchedEdge(mousePositionOnCanvas);
    if(currentTouchedPointData != nullptr)
        polygonsContainer->setHighlight(currentTouchedPointData);
    else if(currentTouchedEdgeData != nullptr)
        polygonsContainer->setHighlight(currentTouchedEdgeData);
    
    if(currentTouchedPointData != nullptr)
        delete currentTouchedPointData;

    if(currentTouchedEdgeData != nullptr)
        delete currentTouchedEdgeData;
}
