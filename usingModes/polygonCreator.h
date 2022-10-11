#pragma once

#include <SFML/Graphics.hpp>
#include "../canvases/canvas.h"
#include "../drawers/pointDrawer.h"
#include "../drawers/lineDrawer.h"
#include <vector>

class PolygonCreator {
public:
    PolygonCreator(PointDrawer* pointDrawer, LineDrawer* lineDrawer, Canvas* canvas, sf::Window* window);
    void update();
    void draw();
    bool isEnd();
    void restart();
    std::vector<sf::Vector2i> getPoints();

private:
    bool isMouseOnFirstPoint(sf::Vector2i mousePosition);
    sf::Vector2i getMousePositionOnCanvas();

    std::vector<sf::Vector2i> points;
    PointDrawer* pointDrawer;
    LineDrawer* lineDrawer;
    Canvas* canvas;
    sf::Window* window;
    bool end;
};
