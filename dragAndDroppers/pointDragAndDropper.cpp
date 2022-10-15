#include "pointDragAndDropper.h"

using namespace sf;

PointDragAndDropper::PointDragAndDropper(TouchedPointData* touchedPointData, LineDrawer* lineDrawer, PointDrawer* pointDrawer, PolygonsContainer *polygonsContainer, Vector2i mousePositionOnCanvas) {
    this->touchedPointData = touchedPointData;
    this->lineDrawer = lineDrawer;
    this->pointDrawer = pointDrawer;
    this->polygonsContainer = polygonsContainer;
    newPointPosition = mousePositionOnCanvas;
}

void PointDragAndDropper::update(Vector2i mousePositionOnCanvas) {
    newPointPosition = mousePositionOnCanvas;
}

void PointDragAndDropper::draw() {
    pointDrawer->draw(newPointPosition, Color::Green);

    auto points = touchedPointData->polygon.getPoints();
    int prev = (touchedPointData->pointIndex - 1 + points.size()) % points.size();
    int next = (touchedPointData->pointIndex + 1) % points.size();
    lineDrawer->draw(newPointPosition, points[prev], Color::Green);
    lineDrawer->draw(newPointPosition, points[next], Color::Green);
}

void PointDragAndDropper::finish() {
    polygonsContainer->updatePolygon(touchedPointData->polygonIndex, touchedPointData->pointIndex, newPointPosition);
}
