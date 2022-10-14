#pragma once

#include "polygon.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "../drawers/lineDrawer.h"
#include "../drawers/pointDrawer.h"

class PolygonsContainer {
public:
    PolygonsContainer(LineDrawer* lineDrawer, PointDrawer* pointDrawer);
    void addPolygon(Polygon polygon);
    void addPolygon(std::vector<sf::Vector2i> points);
    void draw();
    std::vector<Polygon> getPolygons();
    void updatePolygon(int polygonIndex, int pointIndex, sf::Vector2i newPointValue);

private:
    std::vector<Polygon> polygons;
    LineDrawer* lineDrawer;
    PointDrawer* pointDrawer;
};
