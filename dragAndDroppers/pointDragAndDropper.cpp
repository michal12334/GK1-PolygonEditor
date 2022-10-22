#include "pointDragAndDropper.h"

using namespace sf;

PointDragAndDropper::PointDragAndDropper(TouchedPointData* touchedPointData, LineDrawer* lineDrawer, PointDrawer* pointDrawer, PolygonsContainer *polygonsContainer, Vector2i mousePositionOnCanvas) {
    this->touchedPointData = touchedPointData;
    this->lineDrawer = lineDrawer;
    this->pointDrawer = pointDrawer;
    this->polygonsContainer = polygonsContainer;
    previousMousePosition = mousePositionOnCanvas;
    newPolygon = polygonsContainer->getPolygons()[touchedPointData->polygonIndex];
}

void PointDragAndDropper::update(Vector2i mousePositionOnCanvas) {
    auto delta = mousePositionOnCanvas - previousMousePosition;
    previousMousePosition = mousePositionOnCanvas;
    auto points = newPolygon.getPoints();
    newPolygon.updatePoint(touchedPointData->pointIndex, points[touchedPointData->pointIndex] + delta);
}

void PointDragAndDropper::draw() {
    newPolygon.draw(Color::Green);
}

void PointDragAndDropper::finish() {
    polygonsContainer->updatePolygon(touchedPointData->polygonIndex, newPolygon);
}
