#include "polygonsContainer.h"
#include <iostream>

using namespace sf;
using namespace std;

PolygonsContainer::PolygonsContainer(LineDrawer* lineDrawer, PointDrawer* pointDrawer) {
    this->lineDrawer = lineDrawer;
    this->pointDrawer = pointDrawer;
    clearHighlight();
}

void PolygonsContainer::addPolygon(Polygon polygon) {
    polygons.push_back(polygon);
}

void PolygonsContainer::addPolygon(vector<Vector2i> points) {
    addPolygon(Polygon(points, pointDrawer, lineDrawer));
}

void PolygonsContainer::draw() {
    for(int i = 0; i < polygons.size(); i++) {
        if(highlightenPolygonIndex == i && highlightenEdgeIndex != -1)
            polygons[i].drawWithHighlihtenEdge(highlightenEdgeIndex, Color::Red);
        else if(highlightenPolygonIndex == i && highlightenPointIndex != -1)
            polygons[i].drawWithHighlihtenPoint(highlightenPointIndex, Color::Red);
        else
            polygons[i].draw();
    }
}

vector<Polygon> PolygonsContainer::getPolygons() {
    return polygons;
}

void PolygonsContainer::updatePolygon(int polygonIndex, int pointIndex, Vector2i newPointValue) {
    polygons[polygonIndex].updatePoint(pointIndex, newPointValue);
}

void PolygonsContainer::setHighlight(TouchedEdgeData* touchedEdgeData) {
    highlightenPolygonIndex = touchedEdgeData->polygonIndex;
    highlightenEdgeIndex = touchedEdgeData->startPointIndex;
}

void PolygonsContainer::setHighlight(TouchedPointData* touchedPointData) {
    highlightenPolygonIndex = touchedPointData->polygonIndex;
    highlightenPointIndex = touchedPointData->pointIndex;
}

void PolygonsContainer::clearHighlight() {
    highlightenPolygonIndex = -1;
    highlightenPointIndex = -1;
    highlightenEdgeIndex = -1;
}

bool PolygonsContainer::isEdgeHighlighten() {
    return highlightenEdgeIndex != -1;
}

void PolygonsContainer::addPointOnHighlightenEdge() {
    polygons[highlightenPolygonIndex].addPointOnEdge(highlightenEdgeIndex);
}
