#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "../canvases/canvas.h"
#include "../drawers/lineDrawer.h"
#include "../drawers/pointDrawer.h"

class Polygon {
public:
    Polygon(const std::vector<sf::Vector2i>& points, PointDrawer* pointDrawer, LineDrawer* lineDrawer);
    void draw(sf::Color color = sf::Color::Black);
    void drawWithHighlihtenPoint(int pointIndex, sf::Color color);
    void drawWithHighlihtenEdge(int edgeIndex, sf::Color color);
    std::vector<sf::Vector2i> getPoints() const;
    void updatePoint(int index, sf::Vector2i newValue);
    void addPointOnEdge(int edgeIndex);
    void deletePoint(int index);

private:
    std::vector<sf::Vector2i> points;
    PointDrawer* pointDrawer;
    LineDrawer* lineDrawer;
};
