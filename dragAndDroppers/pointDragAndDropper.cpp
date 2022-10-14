#include "pointDragAndDropper.h"

using namespace sf;

PointDragAndDropper::PointDragAndDropper(TouchedPointData* touchedPointData, LineDrawer* lineDrawer, PointDrawer* pointDrawer, PolygonsContainer *polygonsContainer) {
    this->touchedPointData = touchedPointData;
    this->lineDrawer = lineDrawer;
    this->pointDrawer = pointDrawer;
    this->polygonsContainer = polygonsContainer;
}

void PointDragAndDropper::update(Vector2i mousePositionOnCanvas) {
    newPointPosition = mousePositionOnCanvas;
}

void PointDragAndDropper::draw() {
    pointDrawer->draw(newPointPosition);

    auto points = touchedPointData->polygon.getPoints();
    lineDrawer->draw(newPointPosition, points[touchedPointData->pointIndex]);
}

void PointDragAndDropper::finish() {
    polygonsContainer->updatePolygon(touchedPointData->polygonIndex, touchedPointData->pointIndex, newPointPosition);
}
