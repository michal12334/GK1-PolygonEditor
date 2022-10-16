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
        else if(highlightenPolygonIndex == i)
            polygons[i].draw(Color::Red);
        else if(selectedPolygonIndex == i && selectedEdgeIndex != -1)
            polygons[i].drawWithHighlihtenEdge(selectedEdgeIndex, Color::Green);
        else if(selectedPolygonIndex == i && selectedPointIndex != -1)
            polygons[i].drawWithHighlihtenPoint(selectedPointIndex, Color::Green);
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

void PolygonsContainer::setHighlighten(TouchedEdgeData* touchedEdgeData) {
    highlightenPolygonIndex = touchedEdgeData->polygonIndex;
    highlightenEdgeIndex = touchedEdgeData->startPointIndex;
}

void PolygonsContainer::setHighlighten(TouchedPointData* touchedPointData) {
    highlightenPolygonIndex = touchedPointData->polygonIndex;
    highlightenPointIndex = touchedPointData->pointIndex;
}

void PolygonsContainer::setHighlighten(TouchedPolygonData* touchedPolygonData) {
    highlightenPolygonIndex = touchedPolygonData->polygonIndex;
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

void PolygonsContainer::setSelection(TouchedEdgeData* touchedEdgeData) {
    clearHighlight();
    selectedPolygonIndex = touchedEdgeData->polygonIndex;
    selectedEdgeIndex = touchedEdgeData->startPointIndex;
}

void PolygonsContainer::setSelection(TouchedPointData* touchedPointData) {
    clearHighlight();
    selectedPolygonIndex = touchedPointData->polygonIndex;
    selectedPointIndex = touchedPointData->pointIndex;
}

void PolygonsContainer::clearSelection() {
    selectedPolygonIndex = -1;
    selectedPointIndex = -1;
    selectedEdgeIndex = -1;
}

void PolygonsContainer::deleteSelected() {
    if(selectedPolygonIndex == -1)
        return;

    if(selectedPointIndex != -1) {
        polygons[selectedPolygonIndex].deletePoint(selectedPointIndex);
    } else if(selectedEdgeIndex != -1) {
        polygons[selectedPolygonIndex].deletePoint(selectedEdgeIndex);
        polygons[selectedPolygonIndex].deletePoint(selectedEdgeIndex % polygons[selectedPolygonIndex].getPoints().size());
    }

    if(polygons[selectedPolygonIndex].getPoints().size() < 3) {
        polygons.erase(polygons.begin() + selectedPolygonIndex);
    }

    clearSelection();
}

bool PolygonsContainer::isSomethingSelected() {
    return selectedPolygonIndex != -1;
}
