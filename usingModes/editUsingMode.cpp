#include "editUsingMode.h"

using namespace sf;

EditUsingMode::EditUsingMode(
    Window* window,
    Canvas* canvas,
    PointDrawer* pointDrawer,
    LineDrawer* lineDrawer,
    PolygonsContainer* polygonsContainer,
    PointTouchDetector* pointTouchDetector,
    EdgeTouchDetector* edgeTouchDetector,
    PolygonTouchDetector* polygonTouchDetector
) {
    this->window = window;
    this->canvas = canvas;
    this->pointDrawer = pointDrawer;
    this->lineDrawer = lineDrawer;
    this->polygonsContainer = polygonsContainer;
    this->pointTouchDetector = pointTouchDetector;
    this->edgeTouchDetector = edgeTouchDetector;
    this->polygonTouchDetector = polygonTouchDetector;
    
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
    doMouseLeftButtonAction(mousePositionOnCanvas);
    doMouseRightButtonAction(mousePositionOnCanvas);
    doDeleteButtonAction();
}

void EditUsingMode::draw() {
    if(pointDragAndDropper != nullptr)
        pointDragAndDropper->draw();
    else if(edgeDragAndDropper != nullptr)
        edgeDragAndDropper->draw();
    else if(polygonDragAndDropper != nullptr)
        polygonDragAndDropper->draw();
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
    if(polygonsContainer->isSomethingSelected())
        return;

    polygonsContainer->clearHighlight();
    auto currentTouchedPointData = pointTouchDetector->getTouchedPoint(mousePositionOnCanvas);
    auto currentTouchedEdgeData = edgeTouchDetector->getTouchedEdge(mousePositionOnCanvas);
    auto currentTouchedPolygonData = polygonTouchDetector->getTouchedPolygon(mousePositionOnCanvas);
    if(currentTouchedPointData != nullptr)
        polygonsContainer->setHighlighten(currentTouchedPointData);
    else if(currentTouchedEdgeData != nullptr)
        polygonsContainer->setHighlighten(currentTouchedEdgeData);
    else if(currentTouchedPolygonData != nullptr)
        polygonsContainer->setHighlighten(currentTouchedPolygonData);
    
    if(currentTouchedPointData != nullptr)
        delete currentTouchedPointData;

    if(currentTouchedEdgeData != nullptr)
        delete currentTouchedEdgeData;

    if(currentTouchedPolygonData != nullptr)
        delete currentTouchedPolygonData;
}

void EditUsingMode::doMouseLeftButtonAction(Vector2i mousePositionOnCanvas) {
    if(!isMouseLeftButtonPressed && Mouse::isButtonPressed(Mouse::Button::Left)) {
        isMouseLeftButtonPressed = true;
        polygonsContainer->clearSelection();
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
                    auto currentTouchedPolygonData = polygonTouchDetector->getTouchedPolygon(mousePositionOnCanvas);
                    if(currentTouchedPolygonData == nullptr) {
                        polygonCreator->restart();
                        isPolygonBeingDrawn = true;
                        polygonCreator->update();
                    } else {
                        touchedPolygonData = currentTouchedPolygonData;
                        polygonDragAndDropper = new PolygonDragAndDropper(touchedPolygonData, lineDrawer, pointDrawer, polygonsContainer, mousePositionOnCanvas);
                    }
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
            polygonsContainer->setSelection(touchedPointData);
            delete pointDragAndDropper;
            delete touchedPointData;
            pointDragAndDropper = nullptr;
            touchedPointData = nullptr;
        } else if(edgeDragAndDropper != nullptr) {
            edgeDragAndDropper->finish();
            polygonsContainer->setSelection(touchedEdgeData);
            delete edgeDragAndDropper;
            delete touchedEdgeData;
            edgeDragAndDropper = nullptr;
            touchedEdgeData = nullptr;
        } else if(polygonDragAndDropper != nullptr) {
            polygonDragAndDropper->finish();
            delete polygonDragAndDropper;
            delete touchedPolygonData;
            polygonDragAndDropper = nullptr;
            touchedPolygonData = nullptr;
        }
    } else {
        if(pointDragAndDropper != nullptr) {
            pointDragAndDropper->update(mousePositionOnCanvas);
        } else if(edgeDragAndDropper != nullptr) {
            edgeDragAndDropper->update(mousePositionOnCanvas);
        } else if(polygonDragAndDropper != nullptr) {
            polygonDragAndDropper->update(mousePositionOnCanvas);
        }
    }
}

void EditUsingMode::doMouseRightButtonAction(Vector2i mousePositionOnCanvas) {
    if(Mouse::isButtonPressed(Mouse::Button::Right)) {
        if(!isMouseRightButtonPressed) {
            if(polygonsContainer->isEdgeHighlighten())
                polygonsContainer->addPointOnHighlightenEdge();

            if(polygonsContainer->isSomethingSelected())
                polygonsContainer->clearSelection();
        }

        isMouseRightButtonPressed = true;
    } else {
        isMouseRightButtonPressed = false;
    }
}

void EditUsingMode::doDeleteButtonAction() {
    if(Keyboard::isKeyPressed(Keyboard::Key::Delete)) {
        if(!isDeleteButtonPressed) {
            if(polygonsContainer->isSomethingSelected()) {
                polygonsContainer->deleteSelected();
            }
        }
        isDeleteButtonPressed = true;
    } else {
        isDeleteButtonPressed = false;
    }
}
