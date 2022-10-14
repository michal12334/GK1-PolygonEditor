#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "../canvases/canvas.h"
#include "../drawers/lineDrawer.h"
#include "../drawers/pointDrawer.h"

class Polygon {
public:
    Polygon(const std::vector<sf::Vector2i>& points, PointDrawer* pointDrawer, LineDrawer* lineDrawer);
    void draw();
    std::vector<sf::Vector2i> getPoints() const;
    void updatePoint(int index, sf::Vector2i newValue);

private:
    std::vector<sf::Vector2i> points;
    PointDrawer* pointDrawer;
    LineDrawer* lineDrawer;
};
