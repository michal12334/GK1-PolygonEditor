#include "polygonsContainer.h"
#include <iostream>
#include <sstream>
#include <cmath>

using namespace sf;
using namespace std;

PolygonsContainer::PolygonsContainer(LineDrawer* lineDrawer, PointDrawer* pointDrawer, Canvas* canvas) {
    this->lineDrawer = lineDrawer;
    this->pointDrawer = pointDrawer;
    this->canvas = canvas;
    clearHighlight();
    font.loadFromFile("fonts/FuzzyBubbles-Regular.ttf");
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
        else if(selectedPolygonIndex == i)
            polygons[i].draw(Color::Green);
        else
            polygons[i].draw();
    }

    for(const auto& len : lengths) {
        drawLen(len);
    }
}

vector<Polygon> PolygonsContainer::getPolygons() {
    return polygons;
}

void PolygonsContainer::updatePolygon(int polygonIndex, int pointIndex, Vector2i newPointValue) {
    polygons[polygonIndex].updatePoint(pointIndex, newPointValue);
}

void PolygonsContainer::updatePolygon(int polygonIndex, Polygon newPolygonValue) {
    polygons[polygonIndex] = newPolygonValue;
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
    removeEdgeLength(highlightenPolygonIndex, highlightenEdgeIndex);
    polygons[highlightenPolygonIndex].addPointOnEdge(highlightenEdgeIndex);
    int size = polygons[highlightenPolygonIndex].getPoints().size();
    for(int i = 0; i < lengths.size(); i++) {
        if(lengths[i].polygonIndex == highlightenPolygonIndex && lengths[i].edgeIndex > highlightenEdgeIndex) {
            lengths[i].edgeIndex = (lengths[i].edgeIndex + 1) % size;
        }
    }
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

void PolygonsContainer::setSelection(TouchedPolygonData* touchedPolygonData) {
    clearHighlight();
    selectedPolygonIndex = touchedPolygonData->polygonIndex;
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
        int size = polygons[selectedPolygonIndex].getPoints().size();
        removeEdgeLength(selectedPolygonIndex, selectedPointIndex);
        removeEdgeLength(selectedPolygonIndex, (selectedPointIndex - 1 + size) % size);
        size--;
        for(int i = 0; i < lengths.size(); i++) {
            if(lengths[i].polygonIndex == selectedPolygonIndex && lengths[i].edgeIndex > selectedPointIndex) {
                lengths[i].edgeIndex = (lengths[i].edgeIndex - 1 + size) % size;
            }
        }
        polygons[selectedPolygonIndex].deletePoint(selectedPointIndex);
    } else if(selectedEdgeIndex != -1) {
        int size = polygons[selectedPolygonIndex].getPoints().size();
        removeEdgeLength(selectedPolygonIndex, selectedEdgeIndex);
        removeEdgeLength(selectedPolygonIndex, (selectedEdgeIndex - 1 + size) % size);
        removeEdgeLength(selectedPolygonIndex, (selectedEdgeIndex + 1) % size);
        size -= 2;
        for(int i = 0; i < lengths.size(); i++) {
            if(lengths[i].polygonIndex == selectedPolygonIndex && lengths[i].edgeIndex > selectedEdgeIndex + 1) {
                lengths[i].edgeIndex = (lengths[i].edgeIndex - 2 + size) % size;
            }
        }
        polygons[selectedPolygonIndex].deletePoint(selectedEdgeIndex);
        polygons[selectedPolygonIndex].deletePoint(selectedEdgeIndex % size);
    } else {
        removeEdgeLengthsByPolygon(selectedPolygonIndex);
        polygons.erase(polygons.begin() + selectedPolygonIndex);
    }

    if(polygons[selectedPolygonIndex].getPoints().size() < 3) {
        removeEdgeLengthsByPolygon(selectedPolygonIndex);
        polygons.erase(polygons.begin() + selectedPolygonIndex);
    }

    clearSelection();
}

bool PolygonsContainer::isSomethingSelected() {
    return selectedPolygonIndex != -1;
}

void PolygonsContainer::setEdgeLength(TouchedEdgeData* touchedEdgeData, float len) {
    auto pLengths = getLengthByPolygon(touchedEdgeData->polygonIndex);
    auto points = polygons[touchedEdgeData->polygonIndex].getPoints();
    if(pLengths.size() >= points.size() - 1)
        return;
    vector<Vector2f> newPoints;
    for(int i = 0; i < points.size(); i++) {
        newPoints.push_back(Vector2f(points[i].x, points[i].y));
    }
    pLengths.push_back(EdgeLength(touchedEdgeData->polygonIndex, touchedEdgeData->startPointIndex, len));
    int index = touchedEdgeData->startPointIndex;
    while(true) {
        float l = -1;
        for(int i = 0; i < pLengths.size(); i++) {
            if(pLengths[i].edgeIndex == index) {
                l = pLengths[i].len;
                break;
            }
        }
        if(l == -1) {
            break;
        }
        auto versor = getVersor(newPoints[index], newPoints[(index + 1) % points.size()]);
        auto vector = versor * l;
        newPoints[index] = newPoints[(index + 1) % points.size()] + vector;

        index = (index - 1 + newPoints.size()) % newPoints.size();
    }

    for(int i = 0; i < newPoints.size(); i++) {
        polygons[touchedEdgeData->polygonIndex].updatePoint(i, Vector2i(newPoints[i].x, newPoints[i].y));
    }

    lengths.push_back(EdgeLength(touchedEdgeData->polygonIndex, touchedEdgeData->startPointIndex, len));
}

void PolygonsContainer::setEdgeLength(TouchedEdgeData* touchedEdgeData) {
    float len = polygons[touchedEdgeData->polygonIndex].getEdgeLength(touchedEdgeData->startPointIndex);
    setEdgeLength(touchedEdgeData, len);
}

vector<EdgeLength> PolygonsContainer::getLengthByPolygon(int polygonIndex) {
    vector<EdgeLength> result;
    for(int i = 0; i < lengths.size(); i++) {
        if(lengths[i].polygonIndex == polygonIndex)
            result.push_back(lengths[i]);
    }
    return result;
}

void PolygonsContainer::removeEdgeLength(TouchedEdgeData* touchedEdgeData) {
    for(int i = 0; i < lengths.size(); i++) {
        if(lengths[i].edgeIndex == touchedEdgeData->startPointIndex && lengths[i].polygonIndex == touchedEdgeData->polygonIndex) {
            lengths.erase(lengths.begin() + i);
            break;
        }
    }
}

void PolygonsContainer::removeEdgeLength(int polygonIndex, int edgeIndex) {
    for(int i = 0; i < lengths.size(); i++) {
        if(lengths[i].edgeIndex == edgeIndex && lengths[i].polygonIndex == polygonIndex) {
            lengths.erase(lengths.begin() + i);
            break;
        }
    }
}

void PolygonsContainer::removeEdgeLengthsByPolygon(int polygonIndex) {
    for(int i = 0; i < lengths.size(); i++) {
        if(lengths[i].polygonIndex == polygonIndex) {
            lengths.erase(lengths.begin() + i);
            i--;
        }
    }
}

void PolygonsContainer::drawLen(EdgeLength edgeLength) {
    auto points = polygons[edgeLength.polygonIndex].getPoints();
    auto position = (points[edgeLength.edgeIndex] + points[(edgeLength.edgeIndex + 1) % points.size()]) / 2;
    Text* text = new Text();
    text->setFont(font);
    text->setCharacterSize(20);
    text->setPosition(Vector2f(position.x, position.y));
    text->setString(numberToString(edgeLength.len));
    text->setFillColor(sf::Color::Black);
    canvas->drawNative(text);
}

template<typename T>
string PolygonsContainer::numberToString(T num) {
    ostringstream stream;
    stream << num;
    return stream.str();
}

Vector2f PolygonsContainer::getVersor(Vector2f a, Vector2f b) {
    auto result = a - b;
    float len = sqrt(result.x * result.x + result.y * result.y);
    return result / len;
}
