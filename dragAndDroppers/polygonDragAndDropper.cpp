#include "polygonDragAndDropper.h"

using namespace sf;
using namespace std;

PolygonDragAndDropper::PolygonDragAndDropper(
    TouchedPolygonData* touchedPolygonData,
    LineDrawer* lineDrawer,
    PointDrawer* pointDrawer,
    PolygonsContainer *polygonsContainer,
    Vector2i mousePosition
) {
    this->touchedPolygonData = touchedPolygonData;
    this->lineDrawer = lineDrawer;
    this->pointDrawer = pointDrawer;
    this->polygonsContainer = polygonsContainer;
    previousMousePosition = mousePosition;
    newPoints = touchedPolygonData->polygon.getPoints();
}

void PolygonDragAndDropper::update(Vector2i mousePosition) {
    auto delta = mousePosition - previousMousePosition;
    previousMousePosition = mousePosition;
    for(int i = 0; i < newPoints.size(); i++) {
        newPoints[i] += delta;
    }
}

void PolygonDragAndDropper::draw() {
    for(int i = 0; i < newPoints.size(); i++) {
        pointDrawer->draw(newPoints[i], Color::Green);
        lineDrawer->draw(newPoints[i], newPoints[(i + 1) % newPoints.size()], Color::Green);
    }
}

void PolygonDragAndDropper::finish() {
    for(int i = 0; i < newPoints.size(); i++) {
        polygonsContainer->updatePolygon(touchedPolygonData->polygonIndex, i, newPoints[i]);
    }
}
