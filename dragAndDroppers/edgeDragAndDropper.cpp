#include "edgeDragAndDropper.h"

using namespace sf;

EdgeDragAndDropper::EdgeDragAndDropper(
    TouchedEdgeData* touchedEdgeData,
    LineDrawer* lineDrawer,
    PointDrawer* pointDrawer,
    PolygonsContainer *polygonsContainer,
    Vector2i mousePosition)
{
    this->touchedEdgeData = touchedEdgeData;
    this->lineDrawer = lineDrawer;
    this->pointDrawer = pointDrawer;
    this->polygonsContainer = polygonsContainer;
    previousMousePosition = mousePosition;
    
    auto points = touchedEdgeData->polygon.getPoints();
    newStartPointPosition = points[touchedEdgeData->startPointIndex];
    newFinishPointPosition = points[touchedEdgeData->finishPointIndex];
}

void EdgeDragAndDropper::update(Vector2i mousePosition) {
    Vector2i delta = mousePosition - previousMousePosition;
    previousMousePosition = mousePosition;
    newStartPointPosition += delta;
    newFinishPointPosition += delta;
}

void EdgeDragAndDropper::draw() {
    pointDrawer->draw(newStartPointPosition);
    pointDrawer->draw(newFinishPointPosition);
    lineDrawer->draw(newStartPointPosition, newFinishPointPosition);

    auto points = touchedEdgeData->polygon.getPoints();
    int prev = (touchedEdgeData->startPointIndex - 1 + points.size()) % points.size();
    int next = (touchedEdgeData->finishPointIndex + 1) % points.size();
    lineDrawer->draw(newStartPointPosition, points[prev]);
    lineDrawer->draw(newFinishPointPosition, points[next]);
}

void EdgeDragAndDropper::finish() {
    polygonsContainer->updatePolygon(touchedEdgeData->polygonIndex, touchedEdgeData->startPointIndex, newStartPointPosition);
    polygonsContainer->updatePolygon(touchedEdgeData->polygonIndex, touchedEdgeData->finishPointIndex, newFinishPointPosition);
}
