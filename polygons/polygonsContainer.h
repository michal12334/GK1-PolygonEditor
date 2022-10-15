#pragma once

#include "polygon.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "../drawers/lineDrawer.h"
#include "../drawers/pointDrawer.h"
#include "../touchDetectors/touchedEdgeData.h"
#include "../touchDetectors/touchedPointData.h"

class PolygonsContainer {
public:
    PolygonsContainer(LineDrawer* lineDrawer, PointDrawer* pointDrawer);
    void addPolygon(Polygon polygon);
    void addPolygon(std::vector<sf::Vector2i> points);
    void draw();
    std::vector<Polygon> getPolygons();
    void updatePolygon(int polygonIndex, int pointIndex, sf::Vector2i newPointValue);
    void setHighlight(TouchedEdgeData* touchedEdgeData);
    void setHighlight(TouchedPointData* touchedPointData);
    void clearHighlight();

private:
    std::vector<Polygon> polygons;
    LineDrawer* lineDrawer;
    PointDrawer* pointDrawer;

    int highlightenPolygonIndex;
    int highlightenPointIndex;
    int highlightenEdgeIndex;
};
